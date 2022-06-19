/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: ADC						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"
#include "ADC_config.h"

static u8* ADC_pu8Reading= NULL;
static void (*ADC_pvCallBackNotificationFunc)(void)=NULL;

static u8 * ADC_pu8ChainChannelArr = NULL; 			/*Global variable to carry chain array*/
static u8 * ADC_pu8Size = NULL;						/*Global variable to carry cNumbers of channels*/
static u16 * ADC_pu16ChainResultArr = NULL;			/*Global variable to carry chain result*/
static u8 ADC_u8ChainConversionIndex;			/*Global variable to carry the current conversion index*/
static u8 ADC_u8BusyState= IDLE;
static u8 ADC_u8ISRSource;

void ADC_voidInit(void)
{

	/*Voltage Reference Selections for ADC*/
#if VRS == AREF
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif VRS == AVCC
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif VRS == Internal_Voltage

	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);

#else
#error "Wrong Voltage Reference Selections configuration option"
#endif


	/*Select Resolution*/
#if Resolution == _8_Bits
	SET_BIT(ADMUX,ADMUX_ADLAR);

#elif  Resolution == _10_Bits
	CLR_BIT(ADMUX,ADMUX_ADLAR);

#else
#error "Wrong Resolution configuration option"
#endif

	/*Set Prescaler*/
	ADMUX &= 0b11111000;
	ADMUX |= PrescalerSelections;

	/*Enable peripheral*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);


}

u16 ADC_u8GetChannelReading(u8 Copy_u8Channel)
{
	/*Clear the MUX bits in ADMUX register*/
	ADMUX &= 0b11100000;

	/*Set the required channel into MUX bits*/
	ADMUX |= Copy_u8Channel;

	/*Start conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

	/*Polling (busy waiting) until the conversion complete flag is set*/
	while((GET_BIT(ADCSRA,ADCSRA_ADIF))==0);

	/*Clear the conversion complete flag*/
	SET_BIT(ADCSRA,ADCSRA_ADIF);

	/*Return the reading*/
#if Resolution == _8_Bits
	return ADCH;

#elif Resolution == _10_Bits
	return ADC;

#endif
}


u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u8* Copy_pu8Reading)
{
	u32 Local_u32Counter=0;
	u8 Local_u8ErrorState=OK;
	if (ADC_u8BusyState == IDLE)
	{
		/*ADC is now busy*/
		ADC_u8BusyState= BUSY;

		/*Clear the MUX bits in ADMUX register*/
		ADMUX &= 0b11100000;

		/*Set the required channel into the MUX bits*/
		ADMUX|= Copy_u8Channel;

		/*Start conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);

		/*Polling (busy waiting) until the conversion complete flag is set or counter reaching timeout value*/
		while(((GET_BIT(ADCSRA,ADCSRA_ADIF))==0)  && (Local_u32Counter != ADC_u32TIMEOUT ) )
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter== ADC_u32TIMEOUT)
		{
			/*Loop is broken because the timeout is reached*/
			Local_u8ErrorState=NOK;
		}
		else
		{
			/* Loop is broken because flag is raised */
			/*clear the conversion complete flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);

			/*Return the reading*/
#if Resolution == _8_Bits
			*Copy_pu8Reading = ADCH;

#elif Resolution == _10_Bits
			*Copy_pu8Reading =  ADC;

#endif

			/*ADC is finished, return it to IDLE*/
			ADC_u8BusyState= IDLE;
		}
	}
	else
	{
		Local_u8ErrorState= BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel, u8* Copy_pu8Reading, void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_uErrorState=OK;
	if(ADC_u8BusyState== IDLE)
	{
		if((Copy_pu8Reading == NULL) || (Copy_pvNotificationFunc == NULL))
		{
			Local_uErrorState= NULL_POINTER;
		}
		else
		{
			/*make ADC busy in order not to work until being idle*/
			ADC_u8BusyState= BUSY;

			/*Make ISR Source : Chain Asynchronous*/
			ADC_u8ISRSource = SingleChannelAsynch;


			/*Initialize the reading variable globally*/
			ADC_pu8Reading = Copy_pu8Reading;

			/*Initialize the callback notification function globally*/
			ADC_pvCallBackNotificationFunc= Copy_pvNotificationFunc;

			/*Clear the MUX bits in ADMUX register*/
			ADMUX &= 0b11100000;

			/*Set the required channel into the MUX bits*/
			ADMUX|= Copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ADC interrupt enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		Local_uErrorState= BUSY_FUNC;
	}

	return Local_uErrorState;
}

u8 ADC_u8StartChainAsynch(Chain_t * Copy_Chain)
{
	u8 Local_u8ErrorState = OK;
	if(Copy_Chain == NULL)
	{
		return Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		if(ADC_u8BusyState == IDLE)
		{
			ADC_u8BusyState = BUSY;
		}
		else
		{
			/*ADC is now busy*/
			Local_u8ErrorState = BUSY_FUNC;

			/*MakIe ISR Source: Single channel asynchronous*/
			ADC_u8ISRSource = ChainAsynch;

			/*Initialize Chain channel Array*/
			ADC_pu8ChainChannelArr = Copy_Chain->Channel;

			/*Initialize Result Array*/
			ADC_pu16ChainResultArr = Copy_Chain->Result;

			/*Initialize Chain Size*/
			ADC_pu8Size = Copy_Chain->Size;

			/*Initialize Notification function*/
			ADC_pvCallBackNotificationFunc = Copy_Chain->NotificationFunc;

			/*Initialize current conversion Index*/
			ADC_u8ChainConversionIndex = 0;

			/*Clear the MUX bits in ADMUX register*/
			ADMUX &= 0b11100000;

			/*Set the first Channel into the MUX bits*/
			ADMUX|= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ADC interrupt enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}

	}

	return Local_u8ErrorState;

}

void __vector_16 (void)  __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ISRSource == SingleChannelAsynch)
	{
		/*Read ADC result*/
#if Resolution == _8_Bits
		*ADC_pu8Reading = ADCH;

#elif Resolution == _10_Bits
		*ADC_pu8Reading =  ADC;

#endif

		/*Make ADC state be IDLE because it finished*/
		ADC_u8BusyState=IDLE;

		/*Invoke the callback notification function*/
		ADC_pvCallBackNotificationFunc();

		/*Disable ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8ISRSource == ChainAsynch)
	{
		/*read the current conversion*/
#if Resolution == _8_Bits
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex] = ADCH;

#elif Resolution == _10_Bits
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex] = ADC;
#endif

		/*Increment Chain index*/
		ADC_u8ChainConversionIndex++;

		/*check chain is finished or not*/
		if(ADC_u8ChainConversionIndex == ADC_pu8Size)
		{
			/*Chain is finished*/
			/*ADC is now IDLE*/
			ADC_u8BusyState = IDLE;

			/*Invoke the callback notification function*/
			ADC_pvCallBackNotificationFunc();

			/*Disable ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			/*Chain is not finished*/
			/*Set new required channel*/
			ADMUX &= 0b11100000;
			ADMUX|= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];

			/*Start new conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}

	}

}


