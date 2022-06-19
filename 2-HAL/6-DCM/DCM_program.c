/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy          		*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	DC MOTOR								*************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/


#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "DCM_config.h"
#include "DCM_interface.h"
#include "DCM_private.h"



void DCM_voidCW(void)
{
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN0,DIO_u8PIN_HIGH);
}


void DCM_voidCCW(void)
{
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN1,DIO_u8PIN_HIGH);
}
