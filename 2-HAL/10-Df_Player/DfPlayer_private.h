/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy          		*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	DF_Player							    *************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef DfPlayer_PRIVATE_H_
#define DfPlayer_PRIVATE_H_

u8 Command_Array[10];

/* Protocol Index */
#define DFP_MSG_IDX_StartCommand			0
#define DFP_MSG_IDX_VersionInformation		1
#define DFP_MSG_IDX_DataLength				2
#define DFP_MSG_IDX_Command		            3
#define DFP_MSG_IDX_FEEDBACK	            4
#define DFP_MSG_IDX_PARAM_MSB	            5
#define DFP_MSG_IDX_PARAM_LSB	            6
#define DFP_MSG_IDX_CHECK_MSB	            7
#define DFP_MSG_IDX_CHECK_LSB	            8
#define DFP_MSG_IDX_EndCommand		        9

/* Default values */
#define DFP_MSG_StartCommand				0x7E
#define DFP_MSG_VAL_VersionInformation		0xFF
#define DFP_MSG_VAL_DataLength				0x06
#define DFP_MSG_VAL_NOFEEDBACK				0x00
#define DFP_MSG_EndCommand					0xEF

/* Operation commands */
#define DFP_Command_PlayTrackFolder			0x0F

#endif
