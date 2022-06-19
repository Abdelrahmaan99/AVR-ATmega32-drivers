/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy		            *************/
/**************************		Layer:  RTOS STACK								*************/
/**************************		SWC:	RTOS								    *************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_

u8 RTOS_u8CreateTask(u8 Copy_u8Priority , u16 Copy_u16Periodicity , void (*Copy_pvTaskFunc)(void) , u8 Copy_u8FirstDelay);

void RTOS_voidStart(void);

void RTOS_voidSuspendTask(u8 Copy_u8Priority);

void RTOS_voidResumeTask(u8 Copy_u8Priority);

void RTOS_voidDeleteTask(u8 Copy_u8Priority);

#endif
