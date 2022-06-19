/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: SPI						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"
#include "SPI_register.h"

void SPI_voidInitMaster(void)
{
	/*Data Order By Default*/

	/*Master Initialization*/
	SET_BIT(SPCR,SPCR_MASTR);

	/*Clock Polarity By Default*/

	/*Clock Phase By Default*/

	/*Clock Prescaler: Divide by 16 */
	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}

void SPI_voidInitSlave(void)
{
	/*Data Order By Default*/

	/*Slave Initialization*/
	CLR_BIT(SPCR,SPCR_MASTR);

	/*Clock Polarity By Default*/

	/*Clock Phase By Default*/

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}

u8 SPI_u8Transceive(u8 Copy_u8Data)
{
	/*Send the data*/
	SPDR = Copy_u8Data;

	/*Wait (busy waiting) until transfer complete*/
	while(GET_BIT(SPSR,SPSR_SPIF) == 0); /*Time Out*/ /*1*/

	/*Get the exchanged data*/
	return SPDR; /*2*/
	/*1 , 2 Clear Flag*/

}
