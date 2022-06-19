/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy          		*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	DF_Player							    *************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "UART_interface.h"

#include "DfPlayer_config.h"
#include "DfPlayer_private.h"
#include "DfPlayer_interface.h"

#include <util/delay.h>

void DFP_PlayTrackInFolder(u8 Copy_folder, u8 Copy_track)
{
	u8 Local_u8Iterator;

	Command_Array[DFP_MSG_IDX_StartCommand] = DFP_MSG_StartCommand;
	Command_Array[DFP_MSG_IDX_VersionInformation] = DFP_MSG_VAL_VersionInformation;
	Command_Array[DFP_MSG_IDX_DataLength] = DFP_MSG_VAL_DataLength;
	Command_Array[DFP_MSG_IDX_Command] = DFP_Command_PlayTrackFolder;
	Command_Array[DFP_MSG_IDX_FEEDBACK] = DFP_MSG_VAL_NOFEEDBACK;
	Command_Array[DFP_MSG_IDX_PARAM_MSB] = Copy_folder;
	Command_Array[DFP_MSG_IDX_PARAM_LSB] = Copy_track;
	u16 checksum = DFP_Checksum();
	Command_Array[DFP_MSG_IDX_CHECK_MSB] = (checksum & 0xFF00) >> 8;
	Command_Array[DFP_MSG_IDX_CHECK_LSB] = checksum & 0xFF;
	Command_Array[DFP_MSG_IDX_EndCommand] = DFP_MSG_EndCommand;

	for(Local_u8Iterator = 0; Local_u8Iterator <= 10; Local_u8Iterator++)
	{
		USART_voidSend(Command_Array[Local_u8Iterator]);
	}

	//After each command
	_delay_ms(200);



}

u16 DFP_Checksum(void)
{
	u16 checksum = 0;
	checksum  = Command_Array[DFP_MSG_IDX_VersionInformation];
	checksum += Command_Array[DFP_MSG_IDX_DataLength];
	checksum += Command_Array[DFP_MSG_IDX_Command];
	checksum += Command_Array[DFP_MSG_IDX_FEEDBACK];
	checksum += Command_Array[DFP_MSG_IDX_PARAM_MSB];
	checksum += Command_Array[DFP_MSG_IDX_PARAM_LSB];

	checksum = 0xFFFF - checksum + 1;

	return checksum;
}





