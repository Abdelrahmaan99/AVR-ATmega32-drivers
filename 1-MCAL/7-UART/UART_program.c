/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: UART						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_register.h"
#include "UART_config.h"

static u8 USART_DataSend;
static u8 USART_u8BusyState= IDLE;
static u8 USART_u8ISRSource;
static void (*USART_pvCallBackNotificationFunc)(void)=NULL;
static char * USART_pcString = NULL;
static u8 USART_u8ChainCharSendingIndex;

static u8 * USART_RecievedData = NULL;
static u8 USART_BufferSize;
static u8 * USART_ReceivedBuffer = NULL;

void USART_voidInit(void)
{
	u8 Local_u8UCSRCValue = 0;

	/*SET Register UCSRC*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);

	/*SET DATA*/
#if USART_SetData == _5_bit
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif USART_SetData == _6_bit
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif USART_SetData == _7_bit
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif USART_SetData == _8_bit
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif USART_SetData == _9_bit
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	SET_BIT(UCSRB,UCSRB_UCSZ2);

#else
#error "Wrong Choice USART Character Size"
#endif

	/*USART Mode Select*/
#if USART_SelectMode == Asynchronous
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);

	/*Select Speed*/
#if USART_SelectSpeed == NormalSpeed
	CLR_BIT(UCSRA,UCSRA_U2X);

	/*Set Baud Rate*/
	UBRRL = (u8)(((USART_OscillatorFrequency) / (16UL * USART_BaudRate)) - 1);

#elif USART_SelectSpeed == DoubleSpeed
	SET_BIT(UCSRA,UCSRA_U2X);

	UBRRL = (u8)(((USART_OscillatorFrequency) / (8 * USART_BaudRate)) - 1);

#else
#error "Wrong Choice USART Speed"
#endif


#elif USART_SelectMode == Synchronous
	SET_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);

	/*Select Speed*/
	UBRRL = (u8)(((USART_OscillatorFrequency) / (2 * USART_BaudRate)) - 1);

	/*Select Clock Polarity*/
#if USART_ClockPolarity == Rising_Edge
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCPOL);

#elif USART_ClockPolarity == Falling_Edge
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCPOL);

#else
#error "Wrong Choice USART Clock Polarity"
#endif

#else
#error "Wrong Choice USART Mode Select"
#endif

	/*Select parity */
#if USART_SelectParity == Disabled
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM1);

#elif USART_SelectParity == Even
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UPM1);

#elif USART_SelectParity == Odd
	SET_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UPM1);

#error "Wrong Choice USART Parity "
#endif

	/*Stop Bit Select*/
#if USART_StopBitSelect == _1_bit
	CLR_BIT(Local_u8UCSRCValue,UCSRC_USBS);

#elif USART_StopBitSelect == _2_bit
	SET_BIT(Local_u8UCSRCValue,UCSRC_USBS);
#else
#error "Wrong Choice USART Stop Bit Select"
#endif


	/*SET Value of UCSRC*/
	UCSRC = Local_u8UCSRCValue;


	/*Receiver Enable*/
	SET_BIT(UCSRB,UCSRB_RXEN);

	/*Transmitter Enable*/
	SET_BIT(UCSRB,UCSRB_TXEN);
}

void USART_voidSend(u8 Copy_u8Data)
{
	while(GET_BIT(UCSRA,UCSRA_UDRE) == 0);
	UDR = Copy_u8Data;


}

u8 USART_voidSendCharSynch(u8 Copy_u8Data)
{
	u32 Local_u32Counter = 0;
	u8 Local_u8ErrorState = OK;

	//Wait until transmit data is empty
	while(GET_BIT(UCSRA,UCSRA_UDRE) == 0 && (Local_u32Counter != USART_u32TIMEOUT))
	{
		Local_u32Counter++;
	}
	if(Local_u32Counter == USART_u32TIMEOUT)
	{
		/*Loop is broken because the timeout is reached*/
		Local_u8ErrorState = NOK;
	}
	else
	{
		UDR = Copy_u8Data;
	}

	return Local_u8ErrorState;
}

u8 USART_u8SendStringSynch(char * Copy_pcString)
{
    u32 Local_u32Iterrator = 0;
	u8 Local_u8ErrorState = OK;

	if(Copy_pcString == NULL)
	{
		return Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		while(Copy_pcString[Local_u32Iterrator] != '\0')
		{
			USART_voidSendCharSynch(Copy_pcString[Local_u32Iterrator]);
			Local_u32Iterrator++;
		}
	}
	return Local_u8ErrorState;
}

u8 USART_u8SendCharAsynch(u8 Copy_u8Data , void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(USART_u8BusyState== IDLE)
	{
		if((Copy_pvNotificationFunc == NULL))
		{
			Local_u8ErrorState= NULL_POINTER;
		}
		else
		{
			/*make USART busy in order not to work until being idle*/
			USART_u8BusyState= BUSY;

			/*Make ISR Source : SingleCharAsynch*/
			USART_u8ISRSource = SingleCharAsynch;

			/*Initialize globally Data Send*/
			USART_DataSend = Copy_u8Data;

			/*Initialize the callback notification function globally*/
			USART_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*USART Data Register Empty interrupt enable*/
			SET_BIT(UCSRB,UCSRB_UDRIE);
		}
	}
	else
	{
		Local_u8ErrorState= BUSY_FUNC;
	}

	return Local_u8ErrorState;
}



u8 USART_u8SendStringAsynch(char * Copy_pcString , void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState = OK;
	if((Copy_pcString == NULL) || (Copy_pvNotificationFunc == NULL))
	{
		return Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		if(USART_u8BusyState == IDLE)
		{
			USART_u8BusyState = BUSY;
		}
		else
		{
			/*USART is now busy*/
			USART_u8BusyState = BUSY_FUNC;

			/*MakIe ISR Source: ChainCharAsynch*/
			USART_u8ISRSource = ChainCharAsynch;

			/*Initialize Globally Array*/
			USART_pcString = Copy_pcString;

			/*Initialize Notification function*/
			USART_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Initialize current conversion Index*/
			USART_u8ChainCharSendingIndex = 0;

			/*USART Data Register Empty interrupt enable*/
			SET_BIT(UCSRB,UCSRB_UDRIE);
		}

	}

	return Local_u8ErrorState;
}


u8 USART_u8Recieve(void)
{
	while(GET_BIT(UCSRA,UCSRA_RXC) == 0);
	return UDR;
}

u8 USART_u8RecieveCharSynch(void)
{
	u32 Local_u32Counter = 0;
	u8 Local_u8ErrorState = OK;

	//Wait until transmit data is empty
	while(GET_BIT(UCSRA,UCSRA_RXC) == 0 && (Local_u32Counter != USART_u32TIMEOUT))
	{
		Local_u32Counter++;
	}
	if(Local_u32Counter == USART_u32TIMEOUT)
	{
		/*Loop is broken because the timeout is reached*/
		Local_u8ErrorState = NOK;
	}
	else
	{
		return UDR;
	}

	return Local_u8ErrorState;
}

u8 USART_u8RecieveCharAsynch(u8 * Copy_u8ReceivedData,void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(USART_u8BusyState== IDLE)
	{
		if((Copy_pvNotificationFunc == NULL) || (Copy_u8ReceivedData == NULL))
		{
			Local_u8ErrorState= NULL_POINTER;
		}
		else
		{
			/*make USART busy in order not to work until being idle*/
			USART_u8BusyState= BUSY;

			/*Make ISR Source : ReceiveCharAsynch*/
			USART_u8ISRSource = ReceiveCharAsynch;

			/*Initialize globally Data Send*/
			USART_RecievedData = Copy_u8ReceivedData;

			/*Initialize the callback notification function globally*/
			USART_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*USART RX interrupt enable*/
			SET_BIT(UCSRB,UCSRB_RXEN);
		}
	}
	else
	{
		Local_u8ErrorState= BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 USART_voidReceiveBufferSynch(u8 * Copy_u8Buffer , u8 Copy_u8BufferSize)
{

	u8 Local_u8ErrorState;
    u8 Local_u32Iterrator;

	if(Copy_u8Buffer == NULL)
	{
		Local_u8ErrorState= NULL_POINTER;
	}
	else
	{
		for(Local_u32Iterrator = 0; Local_u32Iterrator < Copy_u8BufferSize; Local_u32Iterrator++)
		{
			Copy_u8Buffer[Local_u32Iterrator] = USART_u8RecieveCharSynch();
		}
	}
	return Local_u8ErrorState;
}

u8 USART_voidReceiveBufferAsynch(u8 * Copy_u8Buffer , u8 Copy_u8BufferSize , void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(USART_u8BusyState== IDLE)
	{
		if((Copy_pvNotificationFunc == NULL) || (Copy_u8Buffer == NULL))
		{
			Local_u8ErrorState= NULL_POINTER;
		}
		else
		{
			/*make USART busy in order not to work until being idle*/
			USART_u8BusyState= BUSY;

			/*Make ISR Source : ReceiveBufferAsynch*/
			USART_u8ISRSource = ReceiveBufferAsynch;

			/*Initialize globally Buffer Receive*/
			USART_ReceivedBuffer = Copy_u8Buffer;

			/*Initialize globally Buffer Size*/
			USART_BufferSize = Copy_u8BufferSize;

			/*Initialize the callback notification function globally*/
			USART_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*USART RX interrupt enable*/
			SET_BIT(UCSRB,UCSRB_RXEN);
		}
	}
	else
	{
		Local_u8ErrorState= BUSY_FUNC;
	}

	return Local_u8ErrorState;
}


void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{
	if(USART_u8ISRSource == ReceiveCharAsynch)
	{
		*USART_RecievedData = UDR;

		/*Make USART state be IDLE because it finished*/
		USART_u8BusyState = IDLE;

		/*Invoke the callback notification function*/
		USART_pvCallBackNotificationFunc();

		/*USART RX interrupt Disable*/
		CLR_BIT(UCSRB,UCSRB_RXEN);
	}
	else if(USART_u8ISRSource == ReceiveBufferAsynch)
	{
		static u8 USART_u8BufferIterator = 0;
		/*Receive Buffer*/
		USART_ReceivedBuffer[USART_u8BufferIterator] = UDR;

		/*Increment Buffer index*/
		USART_u8BufferIterator++;

		/*check Buffer is finished or not*/
		if(USART_u8BufferIterator == USART_BufferSize)
		{
			/*Buffer is finished*/
			/*USART is now IDLE*/
			USART_u8BusyState = IDLE;

			/*Invoke the callback notification function*/
			USART_pvCallBackNotificationFunc();

			/*Disable USART RX interrupt*/
			CLR_BIT(UCSRB,UCSRB_RXEN);
		}
		else
		{
			/*Buffer is not finished*/
		}

	}
}

void __vector_15 (void) __attribute__((signal));
void __vector_15 (void)
{

}

/*ISR DATA EMPTY REGISTER*/
void __vector_14 (void) __attribute__((signal));
void __vector_14 (void)
{
	if(USART_u8ISRSource == SingleCharAsynch)
	{

		UDR = USART_DataSend;

		/*Make USART state be IDLE because it finished*/
		USART_u8BusyState = IDLE;

		/*Invoke the callback notification function*/
		USART_pvCallBackNotificationFunc();

		/*Disable USART Data Register Empty interrupt*/
		CLR_BIT(UCSRB,UCSRB_UDRIE);
	}
	else if(USART_u8ISRSource == ChainCharAsynch)
	{
		/*Send Data*/
		UDR = USART_pcString[USART_u8ChainCharSendingIndex];

		/*Increment Chain index*/
		USART_u8ChainCharSendingIndex++;

		/*check chain is finished or not*/
		if(USART_pcString[USART_u8ChainCharSendingIndex] == '\0')
		{
			/*Chain is finished*/
			/*USART is now IDLE*/
			USART_u8BusyState = IDLE;

			/*Invoke the callback notification function*/
			USART_pvCallBackNotificationFunc();

			/*Disable USART Data Register Empty interrupt*/
			CLR_BIT(UCSRB,UCSRB_UDRIE);
		}

	}
}
