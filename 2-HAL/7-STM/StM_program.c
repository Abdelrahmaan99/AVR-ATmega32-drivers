/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy          		*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	STEPER MOTOR							*************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#include <util/delay.h>

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "STM_config.h"
#include "STM_private.h"
#include "STM_interface.h"


void STM_voidCWDefault(void)
{
	DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_LOW);
	_delay_ms(2);
}

void STM_voidCCWDefault(void)
{
	DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_LOW);
	_delay_ms(2);
	DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
	_delay_ms(2);
}

void STM_voidCWByAngle(f32 Copy_f32Angle)
{
	f32 Local_f32NumOfSteps;
	u32 Local_u32Iterator;
	u32 Local_u32Count;

	Local_f32NumOfSteps = (Copy_f32Angle / 0.17578125);
	Local_u32Iterator = (Local_f32NumOfSteps / 4);

	for(Local_u32Count = 0; Local_u32Count < Local_u32Iterator; Local_u32Count++)
	{
		DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_LOW);
		_delay_ms(2);
	}
}

void STM_voidCCWByAngle(f32 Copy_f32Angle)
{
	f32 Local_f32NumOfSteps;
	u32 Local_u32Iterator;
	u32 Local_u32Count;

	Local_f32NumOfSteps = (Copy_f32Angle / 0.17578125);
	Local_u32Iterator = (Local_f32NumOfSteps / 4);

	for(Local_u32Count = 0; Local_u32Count < Local_u32Iterator; Local_u32Count++)
	{

		DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_LOW);
		_delay_ms(2);
		DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(STM_PORT,STM_PIN0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(STM_PORT,STM_PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STM_PORT,STM_PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2);

	}
}



