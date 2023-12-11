#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

void UART_init(void) ;
void UART_vidSend(uint8 u8Data);
uint8 UART_u8Receive(void);
void UART_Send_String (uint8* pu8DataArray);
uint8 UART_Correct_Recieve(void);
void UART_Receive_String (uint8* pu8DataArray);
#endif