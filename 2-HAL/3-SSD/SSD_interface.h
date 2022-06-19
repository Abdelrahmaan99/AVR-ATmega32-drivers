/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	SSD										*************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

/* Preprocessor File Guard */
#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

typedef struct
{
	u8 Port;
	u8 ComType;
	u8 EnablePort;
	u8 EnablePin;
}SSD_t;

#define SSD_u8ANODE				1
#define SSD_u8CATHODE			0

#define SSD_u8NUMBER0			0
#define SSD_u8NUMBER1			1
#define SSD_u8NUMBER2			2
#define SSD_u8NUMBER3			3
#define SSD_u8NUMBER4			4
#define SSD_u8NUMBER5			5
#define SSD_u8NUMBER6			6
#define SSD_u8NUMBER7			7
#define SSD_u8NUMBER8			8
#define SSD_u8NUMBER9			9

u8 SSD_u8SetNumber(u8 Copy_u8Number , SSD_t * SSD);
u8 SSD_u8Enable (SSD_t * SSD);
u8 SSD_u8Disable(SSD_t * SSD);

#endif
