/*********************************************************
********* File       ; DIO_program.c **** program
********* created on : 11/9/2023
********* Author     : Abdullatif Aslam
*********************************************************/

/*********************************************************
*    LAIBRARY INCLUDE                                    *
*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_private.h"
#include "DIO_interface.h"

/*********************************************************
*    FUNCTION OF DIO                                     *
*********************************************************/

Std_ReturnType DIO_udtSetPinDirection 
(
	uint8 u8Port,
	uint8 u8Pin,
	uint8 u8Direction
)
{
	
		Std_ReturnType udtRetrnValue = E_NOT_OK; 
		
		if
		(
		u8Direction == DIO_OUTPUT
		)
		{
			
			switch
			(
			u8Port
			)
			{
				
				case DIO_PORTA:
					SET_BIT(DDRA, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTB:
					SET_BIT(DDRB, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTC:
					SET_BIT(DDRC, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTD: 
					SET_BIT(DDRD, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				default:
	                /*!Comment : Do nothing */
					break;
					
			}
		}
		
		else if
		(
		u8Direction == DIO_INPUT
		)
		{
				switch
				(
				u8Port
				)
				{
					
				case DIO_PORTA: 
					CLR_BIT(DDRA, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTB:
					CLR_BIT(DDRB, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTC: 
					CLR_BIT(DDRC, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTD: 
					CLR_BIT(DDRD, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				default:
	                /*!Comment : Do nothing */
					break;
					
				}
		}
		
		else
		{
			/*!Comment : Do nothing */
		}
		
		return udtRetrnValue;
}

Std_ReturnType DIO_udtSetPinValue 
(
	uint8 u8Port,
	uint8 u8Pin,
	uint8 u8Value
)
{
		Std_ReturnType udtRetrnValue = E_NOT_OK; 
		
		if
		(
		u8Value == DIO_HIGH
		)
		{
			
			switch
			(
			u8Port
			)
			{
				
				case DIO_PORTA: 
					SET_BIT(PORTA, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTB: 
					SET_BIT(PORTB, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTC: 
					SET_BIT(PORTC, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTD: 
					SET_BIT(PORTD, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				default:
	                /*!Comment : Do nothing */
					break;
					
			}
		}
		
		else if
		(
		u8Value == DIO_LOW
		)
		{
				switch
				(
				u8Port
				)
				{
					
				case DIO_PORTA:
					CLR_BIT(PORTA, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTB: 
					CLR_BIT(PORTB, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTC: 
					CLR_BIT(PORTC, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				case DIO_PORTD: 
					CLR_BIT(PORTD, u8Pin);
					udtRetrnValue = E_OK;
					break;
				
				default:
	                /*!Comment : Do nothing */
					break;
					
				}
		}
		
		else
		{
			/*!Comment : Do nothing */
		}
		
		return udtRetrnValue;
}

Std_ReturnType DIO_udtGetPinValue 
(
	uint8  u8Port,
	uint8  u8Pin,
	uint8* pu8Value
)
{
	
	Std_ReturnType udtRetrnValue = E_NOT_OK;
	
	switch
	(
	u8Port
	)
	{
		case DIO_PORTA:
			*pu8Value = GET_BIT(PINA, u8Pin);
			udtRetrnValue = E_OK;
			break;
		
		case DIO_PORTB:
			*pu8Value = GET_BIT(PINB, u8Pin);
			udtRetrnValue = E_OK;
			break;	

		case DIO_PORTC:
			*pu8Value = GET_BIT(PINC, u8Pin);
			udtRetrnValue = E_OK;
			break;			
			
		case DIO_PORTD:
			*pu8Value = GET_BIT(PIND, u8Pin);
			udtRetrnValue = E_OK;
			break;
			
		default :
	           /*!Comment : Do nothing */
			break;
			
	}
	
	return udtRetrnValue;
}

/*****************FILE REVISION**************************
********* Auther name ;
********* Abdullatif Aslam      RRW-Q
*********
********* Updated record:
*********
*********  11/9/2023 RRW-Q V1.0 Updated function of DIO
*********
*********************************************************/