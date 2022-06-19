/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer:  HAL								  	 	*************/
/**************************		SWC:	CLCD									*************/
/**************************		Version:2.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

/* Preprocessor file guard */
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#define NULL					0

#define CLCD_u8NUMBER0			0
#define CLCD_u8NUMBER1			1
#define CLCD_u8NUMBER2			2
#define CLCD_u8NUMBER3			3
#define CLCD_u8NUMBER4			4
#define CLCD_u8NUMBER5			5
#define CLCD_u8NUMBER6			6
#define CLCD_u8NUMBER7			7
#define CLCD_u8NUMBER8			8
#define CLCD_u8NUMBER9			9

void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidInit(void);

void CLCD_voidSendString(const char* Copy_pcString);

void CLCD_voidGoToXY(u8 Copy_u8XPos , u8 Copy_u8YPos);

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern , u8 Copy_u8PatternNumber , u8 Copy_u8XPos , u8 Copy_u8YPos);

void CLCD_voidSendNumber(u32 Copy_u32Number);

#endif
