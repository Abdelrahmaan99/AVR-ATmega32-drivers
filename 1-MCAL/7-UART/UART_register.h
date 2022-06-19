/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: UART						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_

#define UDR					*((volatile u8*)0x2C) 			//USART I/O Data Register

#define UCSRA 					*((volatile u8*)0x2B)		//USART Control and Status Register A
#define UCSRA_U2X				1							//Double the USART Transmission Speed
#define UCSRA_UDRE				5							//USART Data Register Empty
#define UCSRA_TXC				6							//Transmit Complete
#define UCSRA_RXC				7							//USART Receive Complete

#define UCSRB					*((volatile u8*)0x2A)		//USART Control and Status Register B
#define UCSRB_UCSZ2				2							//UCSZ2: Character Size
#define UCSRB_TXEN				3							//Transmitter Enable
#define UCSRB_RXEN				4							//Receiver Enable
#define UCSRB_UDRIE				5							//Data Register Empty Interrupt Enable
#define UCSRB_TXCIE				6
#define UCSRB_RXCIE				7

#define UCSRC					*((volatile u8*)0x40)		//USART Control and Status Register C
#define UCSRC_UCPOL				0							//Clock Polarity
#define UCSRC_UCSZ0				1							//UCSZ0: Character Size
#define UCSRC_UCSZ1				2							//UCSZ0: Character Size
#define UCSRC_USBS				3							//Stop Bit Select
#define UCSRC_UPM0				4							//Parity Mode
#define UCSRC_UPM1				5							//Parity Mode
#define UCSRC_UMSEL				6							//USART Mode Select
#define UCSRC_URSEL				7							//Register Select :UBRRH - UCSRC

#define UBRRL					*((volatile u8*)0x29)		//USART Baud Rate Registers UBRRL


#endif
