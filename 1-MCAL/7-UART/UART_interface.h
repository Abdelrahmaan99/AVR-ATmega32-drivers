/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy	            	*************/
/**************************		Layer: MCAL							            *************/
/**************************		SWC: UART						             	*************/
/**************************		Version: 1.00				             		*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void USART_voidInit(void);
void USART_voidSend(u8 Copy_u8Data);
u8 USART_u8Recieve(void);

u8 USART_voidSendCharSynch(u8 Copy_u8Data);
u8 USART_u8SendStringSynch(char * Copy_pcString);

u8 USART_u8SendCharAsynch(u8 Copy_u8Data , void(*Copy_pvNotificationFunc)(void));
u8 USART_u8SendStringAsynch(char * Copy_pcString , void(*Copy_pvNotificationFunc)(void));

u8 USART_u8RecieveCharSynch(void);
u8 USART_u8RecieveCharAsynch(u8 * Copy_u8ReceivedData,void(*Copy_pvNotificationFunc)(void));

u8 USART_voidReceiveBufferSynch(u8 * Copy_u8Buffer , u8 Copy_u8BufferSize);
u8 USART_voidReceiveBufferAsynch(u8 * Copy_u8Buffer , u8 Copy_u8BufferSize , void(*Copy_pvNotificationFunc)(void));



#endif
