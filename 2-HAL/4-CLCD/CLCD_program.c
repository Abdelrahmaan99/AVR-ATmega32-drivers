/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer:  HAL								  	 	*************/
/**************************		SWC:	CLCD									*************/
/**************************		Version:2.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <util/delay.h>

#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"

static u8 u8AddressCounter = 0;
static u8 u8SateSpecialCharIndx = 0;


void CLCD_voidSendCommand(u8 Copy_u8Command)
{
#if CLCD_MODE == _8_BIT
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_LOW);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8SetPortValue(CLCD_DATA_PORT , Copy_u8Command);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);

#elif CLCD_MODE == _4_BIT

	u8 Local_u8PortValue = 0;

#if CLCD_MSPORT == ENABLED

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8GetPortValue(CLCD_DATA_PORT , &Local_u8PortValue);
	Local_u8PortValue = ((Local_u8PortValue & 0x0f) | (Copy_u8Command & 0xf0));
	DIO_u8SetPortValue(CLCD_DATA_PORT , Local_u8PortValue);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);

	// Second 4_Bits
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8GetPortValue(CLCD_DATA_PORT , &Local_u8PortValue);
	Local_u8PortValue = ((Local_u8PortValue & 0x0f) | (Copy_u8Command << 4));
	DIO_u8SetPortValue(CLCD_DATA_PORT , Local_u8PortValue);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);

#elif CLCD_MSPORT == DISABLED

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8GetPortValue(CLCD_DATA_PORT , &Local_u8PortValue);
	Local_u8PortValue = ((Local_u8PortValue & 0xf0) | (Copy_u8Command >> 4));
	DIO_u8SetPortValue(CLCD_DATA_PORT , Local_u8PortValue);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);

	// Second 4_Bits
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8GetPortValue(CLCD_DATA_PORT , &Local_u8PortValue);
	Local_u8PortValue = ((Local_u8PortValue & 0xf0) | (Copy_u8Command & 0x0f));
	DIO_u8SetPortValue(CLCD_DATA_PORT , Local_u8PortValue);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);
#endif
#endif
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	/* check if send data called because of CLCD_voidWriteSpecialCharacter function or not */
	if(u8SateSpecialCharIndx == 0)
	{
		u8AddressCounter++;
	}
	/* Check End of first line */
	if(u8AddressCounter == END_LINE)
	{
		/* Start from second line */
		CLCD_voidSendCommand(0xC0);
	}

#if CLCD_MODE == _8_BIT
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_HIGH);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8SetPortValue(CLCD_DATA_PORT , Copy_u8Data);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);

#elif CLCD_MODE == _4_BIT

	u8 Local_u8PortValue = 0;

#if CLCD_MSPORT == ENABLED

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8GetPortValue(CLCD_DATA_PORT , &Local_u8PortValue);
	Local_u8PortValue = ((Local_u8PortValue & 0x0f) | (Copy_u8Data & 0xf0));
	DIO_u8SetPortValue(CLCD_DATA_PORT , Local_u8PortValue);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);

	// Second 4_Bits
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8GetPortValue(CLCD_DATA_PORT , &Local_u8PortValue);
	Local_u8PortValue = ((Local_u8PortValue & 0x0f) | (Copy_u8Data << 4));
	DIO_u8SetPortValue(CLCD_DATA_PORT , Local_u8PortValue);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);

#elif CLCD_MSPORT == DISABLED

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8GetPortValue(CLCD_DATA_PORT , &Local_u8PortValue);
	Local_u8PortValue = ((Local_u8PortValue & 0xf0) | (Copy_u8Data >> 4));
	DIO_u8SetPortValue(CLCD_DATA_PORT , Local_u8PortValue);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);

	// Second 4_Bits
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	DIO_u8GetPortValue(CLCD_DATA_PORT , &Local_u8PortValue);
	Local_u8PortValue = ((Local_u8PortValue & 0xf0) | (Copy_u8Data & 0x0f));
	DIO_u8SetPortValue(CLCD_DATA_PORT , Local_u8PortValue);

	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);
#endif
#endif
}

void CLCD_voidInit(void)
{
	_delay_ms(40);
	u8 Local_u8Value = 0;

#if CLCD_MODE == _8_BIT

	/* configure Function Set command bits */
	SET_BIT(Local_u8Value , 4);
	SET_BIT(Local_u8Value , 5);

#if CLCD_LINE == _2_LINE_DISPLAY
	SET_BIT(Local_u8Value , 3);
#endif
#if CLCD_FONT == _5_10_FONT_DISPLAY
	SET_BIT(Local_u8Value , 2);
#endif

	/* Send Function Set Command */
	CLCD_voidSendCommand(Local_u8Value);

	/* Clear Buffer */
	Local_u8Value = 0;

	/* configure Display Control command bits  */
	SET_BIT(Local_u8Value , 3);

#if CLCD_DISPLAY == ENABLED
	SET_BIT(Local_u8Value , 2);
#endif

#if CLCD_CURSOR == ENABLED
	SET_BIT(Local_u8Value , 1);
#endif

#if CLCD_BLINK_CURSOR == ENABLED
	SET_BIT(Local_u8Value , 0);
#endif

	/* Send Display Control command  */
	CLCD_voidSendCommand(Local_u8Value);

	/* Send Display Clear command  */
	CLCD_voidSendCommand(1);
#elif CLCD_MODE == _4_BIT
	/*Init 4-Bit Mode*/
	CLCD_voidSendCommand(0x33);
	CLCD_voidSendCommand(0x32);

    /* configure Function Set command bits */
	SET_BIT(Local_u8Value , 5);
#if CLCD_LINE == _2_LINE_DISPLAY
	SET_BIT(Local_u8Value , 3);
#endif
#if CLCD_FONT == _5_10_FONT_DISPLAY
	SET_BIT(Local_u8Value , 2);
#endif
	/* Send Function Set Command */
	CLCD_voidSendCommand(Local_u8Value);

	/* Clear Buffer */
	Local_u8Value = 0;

	/* configure Display Control command bits  */
	SET_BIT(Local_u8Value , 3);

#if CLCD_DISPLAY == ENABLED
	SET_BIT(Local_u8Value , 2);
#endif

#if CLCD_CURSOR == ENABLED
	SET_BIT(Local_u8Value , 1);
#endif

#if CLCD_BLINK_CURSOR == ENABLED
	SET_BIT(Local_u8Value , 0);
#endif

	/* Send Display Control command  */
	CLCD_voidSendCommand(Local_u8Value);

	/* Send Display Clear command  */
	CLCD_voidSendCommand(1);
#else
#endif
}

void CLCD_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter = 0;
	while(Copy_pcString[Local_u8Counter] != '\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void CLCD_voidGoToXY(u8 Copy_u8XPos , u8 Copy_u8YPos)
{
	u8 Local_u8Adress;
	if(Copy_u8XPos == 0)
	{
		Local_u8Adress = Copy_u8YPos;
	}
	else if(Copy_u8XPos == 1)
	{
		Local_u8Adress = Copy_u8YPos + 0x40;
	}
	CLCD_voidSendCommand(Local_u8Adress + 128);
}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern , u8 Copy_u8PatternNumber , u8 Copy_u8XPos , u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAdress = 0;
	u8 Local_u8Iterator;
	u8SateSpecialCharIndx = 1;

	Local_u8CGRAMAdress = Copy_u8PatternNumber * 8;
	CLCD_voidSendCommand(Local_u8CGRAMAdress + 64);

	for(Local_u8Iterator = 0 ; Local_u8Iterator < 8 ; Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}
	CLCD_voidGoToXY(Copy_u8XPos , Copy_u8YPos);
	CLCD_voidSendData(Copy_u8PatternNumber);
	u8SateSpecialCharIndx = 0;
}

void CLCD_voidSendNumber(u32 Copy_u32Number)
{
	u8 Local_u8DigitNumber;
	s8 Local_s8Counter = -1 , Local_s8Iterator;
	u8 Array_Number[CLCD_SIZE_OF_ARRAY];
	do
	{
		Local_s8Counter++;
		Local_u8DigitNumber = Copy_u32Number % 10;
		Array_Number[Local_s8Counter] = Local_u8DigitNumber + '0';
		Copy_u32Number /= 10;
	}while(Copy_u32Number != 0);
	for(Local_s8Iterator = Local_s8Counter; Local_s8Iterator >= 0; Local_s8Iterator--)
	{
		CLCD_voidSendData(Array_Number[Local_s8Iterator]);
	}
}
