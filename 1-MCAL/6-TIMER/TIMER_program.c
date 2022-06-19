/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: TIMER						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"
#include "TIMER_config.h"

static void (*TIMER0_pvCallBackFunc)(void) = NULL;

static void(*ICU_pvCallBackFunc)(void) = NULL;

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

	/*Set compare match value to 64 For Duty Cycle 25%*/
	OCR0 = 64;


	/*Set Timer : Prescaler Division by 8*/
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
}

void Timer0_voidSetCompMatchValue(u8 Copy_u8value)
{
	OCR0 = Copy_u8value;
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






void TIMER1_voidInit(void)
{
	/*Normal Mode , Default*/
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	/*Waveform Generation Mode, Fast PWM ICR1*/ //Default Normal
	/*CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);*/

	/*Set prescaler Division by 8*/
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
}

void Timer1_voidSetTimerValue(u16 Copy_u16Value)
{
	TCNT1 = Copy_u16Value;
}

u16 Timer1_voidReadTimerValue(void)
{
	return TCNT1;
}
void Timer1_voidSetICRValue(u16 Copy_u8value)
{
	ICR1 = Copy_u8value;
}
void Timer1_voidSetChannelACompMatchValue(u16 Copy_u8value)
{
	OCR1A = Copy_u8value;
}









void ICU_voidInit(void)
{
	/*Set trigger source to rising edge initially*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	/*Enable input capture interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

u8 ICI_u8SetTriggerEdge(u8 Copyu8Edge)
{
	u8 Local_u8ErrorStatus = OK;
	if(Copyu8Edge == ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copyu8Edge == ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}

void ICU_voidEnableInterrupt(void)
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void ICU_voidDisableInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

u16 ICU_u16ReadInputCapture(void)
{
	return ICR1;
}

u8 ICU_u8SetCallBack(void (*Copy_puCallBackFunc))
{
	u8 Local_u8ErrorStatus = OK;
	if(Copy_puCallBackFunc != NULL)
	{
		ICU_pvCallBackFunc = Copy_puCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}

	return Local_u8ErrorStatus;
}






void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}

/*ICU ISR*/
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(ICU_pvCallBackFunc != NULL)
	{
		ICU_pvCallBackFunc();
	}
}

