/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer:  HAL								   		*************/
/**************************		SWC:	CLCD									*************/
/**************************		Version:2.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

/* Preprocessor file guard */
#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

#define CLCD_DATA_PORT			DIO_u8PORTA

#define CLCD_MSPORT				DISABLED

#define CLCD_CTRL_PORT			DIO_u8PORTC
#define CLCD_RS_PIN				DIO_u8PIN0
#define CLCD_RW_PIN				DIO_u8PIN1
#define CLCD_E_PIN				DIO_u8PIN2

/*Choose :   1- _4_BIT
             2- _8_BIT
*/
#define CLCD_MODE			    _4_BIT

/*Choose :   1- _1_LINE_DISPLAY
             2- _2_LINE_DISPLAY
*/
#define CLCD_LINE			    _2_LINE_DISPLAY

/*Choose :   1- _5_7_FONT_DISPLAY
             2- _5_10_FONT_DISPLAY                   * To choose this mode , you must select  _1_LINE_DISPLAY
*/
#define CLCD_FONT				_5_7_FONT_DISPLAY

/*Choose :   1- ENABLED
             2- DISABLED
*/
#define CLCD_DISPLAY			ENABLED
#define CLCD_CURSOR				DISABLED
#define CLCD_BLINK_CURSOR		DISABLED

#endif