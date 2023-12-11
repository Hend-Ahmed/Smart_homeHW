/*********************************************************
********* File       ; DIO_interface.H **** INTERFACE
********* created on : 11/9/2023
********* Author     : Abdullatif Aslam
*********************************************************/

/*********************************************************
*    DIO_INTERFACE  GIDE                                 *
*********************************************************/

#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_

/*********************************************************
*   THE DIRECTION OF PORTX                               *
*********************************************************/

#define DIO_INPUT  ((uint8)0u)
#define DIO_OUTPUT ((uint8)1u)

/*********************************************************
*   THE VALUE OF PORTX                                   *
*********************************************************/

#define DIO_LOW  ((uint8)0u)
#define DIO_HIGH ((uint8)1u)

/*********************************************************
*   THE  PORTX DEFINEATION                               *
*********************************************************/

#define DIO_PORTA ((uint8)0u)
#define DIO_PORTB ((uint8)1u)
#define DIO_PORTC ((uint8)2u)
#define DIO_PORTD ((uint8)3u)

/*********************************************************
*   THE  PINX DEFINEATION                                *
*********************************************************/

#define DIO_PIN0 ((uint8)0u)
#define DIO_PIN1 ((uint8)1u)
#define DIO_PIN2 ((uint8)2u)
#define DIO_PIN3 ((uint8)3u)
#define DIO_PIN4 ((uint8)4u)
#define DIO_PIN5 ((uint8)5u)
#define DIO_PIN6 ((uint8)6u)
#define DIO_PIN7 ((uint8)7u)

/*********************************************************
*   THE  STATUSE OF PORTX                                *
*********************************************************/

#define DIO_FULL_PORT  0xFF
#define DIO_UPPER_PORT 0xF0
#define DIO_LOWER_PORT 0x0F

/*********************************************************
*    FUNCTION OF DIO                                     *
*********************************************************/

Std_ReturnType DIO_udtSetPinDirection 
(
	uint8 u8Port,
	uint8 u8Pin,
	uint8 u8Direction
);

Std_ReturnType DIO_udtSetPinValue 
(
	uint8 u8Port,
	uint8 u8Pin,
	uint8 u8Value
);

Std_ReturnType DIO_udtGetPinValue 
(
	uint8  u8Port,
	uint8  u8Pin,
	uint8* pu8Value
);

#endif

/*****************FILE REVISION*************************
********* Auther name ;
********* Abdullatif Aslam      RRW-Q
*********
********* Updated record:
*********
********* 11/7/2023 RRW-Q SY.0 Updated function of DIO
*********
*******************************************************/

