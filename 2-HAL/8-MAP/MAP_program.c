/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy          		*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	MAP							            *************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "MAP_config.h"
#include "MAP_private.h"
#include "MAP_interface.h"
s32 Map(s32 Copy_s32InputMin , s32 Copy_s32InputMax , s32 Copy_s32OutputMin , s32 Copy_s32OutputMax , s32 Copy_s32InputVal)
{
	s32 Loacl_s32Value = Copy_s32InputVal - Copy_s32InputMin;
	Loacl_s32Value = Loacl_s32Value * (Copy_s32OutputMax - Copy_s32OutputMin);
	Loacl_s32Value = Loacl_s32Value / (Copy_s32InputMax - Copy_s32InputMin);
	Loacl_s32Value = Loacl_s32Value + Copy_s32OutputMin;
	return Loacl_s32Value;
}




