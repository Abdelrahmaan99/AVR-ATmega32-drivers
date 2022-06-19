/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: SPI						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_

#define	SPDR	            *((volatile u8*)0x2F) 		/*SPI Data register*/

#define SPSR    	        *((volatile u8*)0x2E)		/*SPI Status register*/
#define SPSR_SPIF			7							/*SPI Interrupt Flag*/
#define SPSR_SPI2X			0							/*Prescaler bit 2*/

#define SPCR        	    *((volatile u8*)0x2D)		/*SPI Control register*/
#define SPCR_SPE			6							/*SPI Enable*/
#define SPCR_MASTR			4							/*Master bit*/
#define SPCR_SPR1			1							/*Prescaler bit 1*/
#define SPCR_SPR0			0							/*Prescaler bit 0*/

#endif
