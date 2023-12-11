/*********************************************************
********* File       ; DIO_private.h **** DIO PRAIVATE
********* created on : 11/9/2023
********* Author     : Abdullatif Aslam
*********************************************************/

/*********************************************************
*    DIO_PRIVATE GIDE                                    *
*********************************************************/

#ifndef _DIO_PRIVATE_H_
#define _DIO_PRIVATE_H_

/*********************************************************
*    PORTX REGISTERS                                     *
*********************************************************/

/*!Comment : DDRA , PORTA , PINA Defintion */

#define PORTA *((volatile uint8*)0x3B)
#define DDRA  *((volatile uint8*)0x3A)
#define PINA  *((volatile uint8*)0x39)

/*!Comment : DDRB , PORTB , PINB Defintion */

#define PORTB *((volatile uint8*)0x38)
#define DDRB  *((volatile uint8*)0x37)
#define PINB  *((volatile uint8*)0x36)

/*!Comment : DDRC , PORTC , PINC Defintion */

#define PORTC *((volatile uint8*)0x35)
#define DDRC  *((volatile uint8*)0x34)
#define PINC  *((volatile uint8*)0x33)

/*!Comment : DDRD , PORTD , PIND Defintion */

#define PORTD *((volatile uint8*)0x32)
#define DDRD  *((volatile uint8*)0x31)
#define PIND  *((volatile uint8*)0x30)


#endif

/*****************FILE REVISION**************************
********* Auther name ;
********* Abdullatif Aslam      RRW-Q
*********
********* Updated record:
*********
*********  11/9/2023 RRW-Q SY.0 Updated PORTX PRAIVATE
*********
*********************************************************/