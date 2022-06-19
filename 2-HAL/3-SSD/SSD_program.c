/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	SSD										*************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"

u8 SSD_u8SetNumber(u8 Copy_u8Number , SSD_t * SSD)
{
	u8 Local_u8ErrorState = 0;
	/*SSD_ANODE*/
	u8 seven_seg[SSD_u8SIZE_OF_ARRAY] = {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};
	if((SSD -> ComType) == SSD_u8ANODE)
	{
		switch(Copy_u8Number)
		{
		case SSD_u8NUMBER0: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER0]); break;
		case SSD_u8NUMBER1: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER1]); break;
		case SSD_u8NUMBER2: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER2]); break;
		case SSD_u8NUMBER3: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER3]); break;
		case SSD_u8NUMBER4: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER4]); break;
		case SSD_u8NUMBER5: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER5]); break;
		case SSD_u8NUMBER6: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER6]); break;
		case SSD_u8NUMBER7: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER7]); break;
		case SSD_u8NUMBER8: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER8]); break;
		case SSD_u8NUMBER9: DIO_u8SetPortValue(SSD -> Port , seven_seg[SSD_u8NUMBER9]); break;
		default: Local_u8ErrorState = 1; break;
		}
	}
	else if((SSD -> ComType) == SSD_u8CATHODE)
	{
		switch(Copy_u8Number)
		{
		case SSD_u8NUMBER0: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER0]); break;
		case SSD_u8NUMBER1: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER1]); break;
		case SSD_u8NUMBER2: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER2]); break;
		case SSD_u8NUMBER3: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER3]); break;
		case SSD_u8NUMBER4: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER4]); break;
		case SSD_u8NUMBER5: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER5]); break;
		case SSD_u8NUMBER6: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER6]); break;
		case SSD_u8NUMBER7: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER7]); break;
		case SSD_u8NUMBER8: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER8]); break;
		case SSD_u8NUMBER9: DIO_u8SetPortValue(SSD -> Port , ~seven_seg[SSD_u8NUMBER9]); break;
		default: Local_u8ErrorState = 1; break;
		}
	}
	else
	{
		Local_u8ErrorState = 1;
	}
	return Local_u8ErrorState;
}

u8 SSD_u8Enable(SSD_t * SSD)
{
	u8 Local_u8ErrorState = 0;
	if((SSD -> ComType) == SSD_u8ANODE)
	{
		DIO_u8SetPinValue(SSD -> EnablePort , SSD -> EnablePin , DIO_u8PIN_HIGH);
	}
	else if((SSD -> ComType) == SSD_u8CATHODE)
	{
		DIO_u8SetPinValue(SSD -> EnablePort , SSD -> EnablePin , DIO_u8PIN_LOW);
	}
	else
	{
		Local_u8ErrorState = 1;
	}
	return Local_u8ErrorState;
}

u8 SSD_u8Disable(SSD_t * SSD)
{
	u8 Local_u8ErrorState = 0;
	if((SSD -> ComType) == SSD_u8ANODE)
	{
		DIO_u8SetPinValue(SSD -> EnablePort , SSD -> EnablePin , DIO_u8PIN_LOW);
	}
	else if((SSD -> ComType) == SSD_u8CATHODE)
	{
		DIO_u8SetPinValue(SSD -> EnablePort , SSD -> EnablePin , DIO_u8PIN_HIGH);
	}
	else
	{
		Local_u8ErrorState = 1;
	}
	return Local_u8ErrorState;
}