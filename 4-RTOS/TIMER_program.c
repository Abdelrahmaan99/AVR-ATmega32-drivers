/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy		            *************/
/**************************		Layer:  MCAL     								*************/
/**************************		SWC:	TIMER								    *************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"
#include "TIMER_config.h"

static void (*TIMER0_pvCallBackFunc)(void) = NULL;



void TIMER0_voidInit(void)
{
	/*Select MODE*/
#if TIMER_SelectMode == Timer_NormalMode
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);

	/*Enable Over Flow Interrupt*/
	SET_BIT(TIMSK,TIMSK_TOIE0);

	/*Set preLoad*/
	TCNT0 = 0;

#elif TIMER_SelectMode == Timer_PWMPhaseCorrectMode
	SET_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);

#elif TIMER_SelectMode == Timer_CTCMode
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	
	/*Set compare match value to 125 For 1ms compare time*/
	OCR0 = 125;
	
	/*Output compare match interrupt enable*/
	SET_BIT(TIMSK,TIMSK_OCIE0);



#elif TIMER_SelectMode == Timer_FastPWMMode
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*SET on Top, Clear on Compare*/
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);

#else
#error "Wrong Select Mode"
#endif


	/*Set Timer : Prescaler Division by 64*/
	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
}

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}











/* CTC_ISR */
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}