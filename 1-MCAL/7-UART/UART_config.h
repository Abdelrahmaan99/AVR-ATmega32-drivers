/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: UART						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*Select Mode
 * Choose:	1-Asynchronous
 * 			2-Synchronous
 */
#define USART_SelectMode			       Asynchronous

/*Set Parity Mode
 * Choose:	1-Disabled
 * 			2-Even
 * 			3-Odd
 */
#define USART_SelectParity			       Disabled

/*Stop Bit Select
 * Choose: 1-_1_bit
 * 		   2-_2_bit
 */
#define USART_StopBitSelect			       _2_bit

/*Select Character Size
 * Choose: 1-_5_bit
 * 		   2-_6_bit
 * 		   3-_7_bit
 * 		   4-_8_bit
 * 		   5-_9_bit
 */
#define USART_SetData				       _8_bit

/*Select Clock Polarity
 * Choose: 1-Rising_Edge
 * 		   2-Falling_Edge
 */
#define USART_ClockPolarity			       Rising_Edge

/*SET Baud Rate*/
#define USART_BaudRate				       9600

/*Set Oscillator Frequency*/
#define USART_OscillatorFrequency	       8000000

/*Select Speed
 * Choose: 1-NormalSpeed
 * 		   2-DoubleSpeed
 */
#define USART_SelectSpeed			       NormalSpeed

/*Set TimeOut*/
#define USART_u32TIMEOUT		           50000

#endif
