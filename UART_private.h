#ifndef _UART_PRIVATE_H_
#define _UART_PRIVATE_H_



/*********************************************************
*    PORTX REGISTERS                                     *
*******************************************************/

#define UCSRC *((uint8*)0x40u)
#define UCSRA *((uint8*)0x2Bu)
#define UCSRB *((uint8*)0x2Au)
#define UBRRL *((uint8*)0x29u)

#define UDR *((uint8*)0x2cu)



#endif