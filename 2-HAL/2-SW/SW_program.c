/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	             	*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	SW										*************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"

#include "SW_interface.h"
#include "SW_config.h"
#include "SW_private.h"

u8 SW_u8GetState(SW_t * SW , u8* Copy_pu8State)
{
	u8 Local_u8ErrorState = 0;
	u8 Local_u8State = 0;
	if((Copy_pu8State != NULL))
	{
		if((SW -> PullType) == SW_u8PULL_UP)
		{
			DIO_u8SetPinValue(SW -> Port , SW -> Pin , DIO_u8PIN_HIGH);
			DIO_u8GetPinValue(SW -> Port , SW -> Pin , &Local_u8State);

			if(Local_u8State == SW_u8PIN_LOW)
			{
				*Copy_pu8State = SW_u8PRESSED;
			}
			else
			{
				*Copy_pu8State = SW_u8NOT_PRESSED;
			}
		}
		else if((SW -> PullType) == SW_u8PULL_DOWN)
		{
			DIO_u8SetPinValue(SW -> Port , SW -> Pin , DIO_u8PIN_LOW);
			DIO_u8GetPinValue(SW -> Port , SW -> Pin , &Local_u8State);

			if(Local_u8State == SW_u8PIN_HIGH)
			{
				*Copy_pu8State = SW_u8PRESSED;
			}
			else
			{
				*Copy_pu8State = SW_u8NOT_PRESSED;
			}
		}
		else
		{
			Local_u8ErrorState = 1;
		}
	}
	else
	{
		Local_u8ErrorState = 1;
	}
	return Local_u8ErrorState;
}