/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy		            *************/
/**************************		Layer:  MCAL     								*************/
/**************************		SWC:	TIMER								    *************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define TCCR0					*((volatile u8*)0x53)		//Timer0 control register
#define TCCR0_WGM00				6				    		//Wavefoem generation Mode bit0
#define TCCR0_WGM01				3							//Wavefoem generation Mode bit1
#define TCCR0_CS02				2 							//Prescaler bit2
#define TCCR0_CS01				1							//Prescaler bit1
#define TCCR0_CS00				0							//Prescaler bit0

#define TCNT0					*((volatile u8*)0x52)		//Timer/Counter Register

#define OCR0 					*((volatile u8*)0x5C)		//Output compare register 0

#define TIMSK					*((volatile u8*)0x59)		//TIMER MASK
#define TIMSK_TOIE0				0							//Timer/Counter0 Overflow Interrupt Enable
#define TIMSK_OCIE0				1							//Output compare 0 interrupt enable
#define TIMSK_TICIE1			5							//Timer1 input capture interrupt enable

#define TCCR1A					*((volatile u8*)0x4F)		//Timer1 control registerA
#define TCCR1A_WGM10			0
#define TCCR1A_WGM11			1
#define TCCR1A_COM1A0			6
#define TCCR1A_COM1A1			7

#define	TCCR1B					*((volatile u8*)0x4E)		//Timer1 control registerB
#define	TCCR1B_CS10				0
#define	TCCR1B_CS11				1
#define	TCCR1B_CS12				2
#define	TCCR1B_WGM12			3
#define	TCCR1B_WGM13			4
#define TCCR1B_ICES1			6 							//Input capture edge select

#define TCNT1					*((volatile u16*)0x4C)		//Timer1 control register

#define ICR1					*((volatile u16*)0x46)		//Input Capture Register1
#define OCR1A 					*((volatile u16*)0x4A)		//Output compare registerA

#endif
