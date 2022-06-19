/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy          		*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	STEPER MOTOR							*************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef STM_INTERFACE_H_
#define STM_INTERFACE_H_

void STM_u8CWDefault(void);
void STM_u8CCWDefault(void);

void STM_voidCWByAngle(f32 Copy_f32Angle);
void STM_voidCCWByAngle(f32 Copy_f32Angle);



#endif


