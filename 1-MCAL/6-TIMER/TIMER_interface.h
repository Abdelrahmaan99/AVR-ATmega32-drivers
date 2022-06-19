/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: TIMER						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define ICU_RISING_EDGE			1
#define ICU_FALLING_EDGE		0
void TIMER0_voidInit(void);

void Timer0_voidSetCompMatchValue(u8 Copy_u8value);

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));

void TIMER1_voidInit(void);

void Timer1_voidSetTimerValue(u16 Copy_u16Value);

u16 Timer1_voidReadTimerValue(void);

void Timer1_voidSetICRValue(u16 Copy_u8value);

void Timer1_voidSetChannelACompMatchValue(u16 Copy_u8value);

void ICU_voidInit(void);

u8 ICI_u8SetTriggerEdge(u8 Copyu8Edge);

void ICU_voidEnableInterrupt(void);

void ICU_voidDisableInterrupt(void);

u16 ICU_u16ReadInputCapture(void);

u8 ICU_u8SetCallBack(void (* Copy_puCallBackFunc));
#endif
