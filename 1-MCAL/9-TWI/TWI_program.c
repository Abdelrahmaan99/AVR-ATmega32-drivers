/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: TWI						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_config.h"
#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_register.h"

/*Set master address to 0 if master will not be addressed*/
void TWI_voidInitMaster(u8 Copy_u8Address)
{
	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Set SCL frequency to 400kHz, with 8Mhz system frequency*/
	/*1- Set TWBR to 2*/
	TWBR = 2;
	/*2- Clear the prescaler bits (TWPS)*/
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);

	/*Check if the master node will be addressed*/
	if(Copy_u8Address != 0)
	{
		/*Set the required address in the 7 MSB of TWAR*/
		TWAR = Copy_u8Address<<1;
	}
	else
	{
		/*Do nothing*/
	}

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidInitSlave(u8 Copy_u8Address)
{
	/*Set the slave address*/
	TWAR = Copy_u8Address<<1;

	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}

TWI_ErrStatus TWI_SendStartCondition(void)
{
	TWI_ErrStatus Local_Error= NoError;

	/*Send start condition*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) != START_ACK )
	{
		Local_Error = StartConditionErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}

TWI_ErrStatus TWI_SendRepeatedStart(void)
{
	TWI_ErrStatus Local_Error= NoError;

	/*Send start condition*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) != REP_START_ACK )
	{
		Local_Error = RepeatedStartError;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error= NoError;

	/*send the 7bit slave address to the bus*/
	TWDR = Copy_u8SlaveAddress <<1;
	/*set the write request in the LSB in the data register*/
	CLR_BIT(TWDR,0);

	/*Clear the start condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK )
	{
		Local_Error = SlaveAddressWithWriteErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}

TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error= NoError;

	/*send the 7bit slave address to the bus*/
	TWDR = Copy_u8SlaveAddress <<1;
	/*set the read request in the LSB in the data register*/
	SET_BIT(TWDR,0);

	/*Clear the start condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK )
	{
		Local_Error = SlaveAddressWithReadErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}

TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrStatus Local_Error= NoError;

	/*Write the data byte on the bus*/
	TWDR = Copy_u8DataByte;

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) !=  MSTR_WR_BYTE_ACK)
	{
		Local_Error = MasterWriteByteErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}

TWI_ErrStatus TWI_MasterReadDataByte(u8* Copy_pu8DataByte)
{
	TWI_ErrStatus Local_Error= NoError;

	/*Clear the interrupt flag to allow the slave send the data*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) !=  MSTR_RD_BYTE_WITH_ACK)
	{
		Local_Error = MasterReadByteErr;
	}
	else
	{
		/*Read the received data*/
		*Copy_pu8DataByte = TWDR;
	}

	return Local_Error;
}

void TWI_SendStopCondition(void)
{
	/*Sent a stop condition on the bus*/
	SET_BIT(TWCR,TWCR_TWSTO);

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

}
