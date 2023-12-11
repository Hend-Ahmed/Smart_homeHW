#ifndef _KEYPAD_CONFIG_H_
#define _KEYPAD_CONFIG_H_

#include "DIO_interface.h"

#define F_CPU 16000000UL
#include <util/delay.h>


/// ( \ )= to take next line and avoid "Enter" cause #define takes only 1 line
#define KPD_BUTTONS	 {{'D', 'C', 'B', 'A'}, {'#', '9', '6', '3'}, {'*', '7', '4', '1'}, {'0', '8', '5', '2'}} 
	
	//#define KPD_BUTTONS	 { {'D', 'C', 'B', 'A'}, {'#', '9', '6', '3'}, {'0', '8', '5', '2'}, {'*', '7', '4', '1'}}

#define KEYPAD_NO_PRESSED_KEY 0XFF


#define KEYPAD_Row_PORT	   DIO_PORTB 
 #define KEYPAD_Column_PORT  DIO_PORTC		// WHEN Connecting el kpd normal side
							
 #define KEYPAD_R0_PIN  DIO_PIN7			/// TO MY RIGHT WHEN NUMBERS SIDE TO MY FACE AND WHITE SIDE TO FLOOR
 #define KEYPAD_R1_PIN  DIO_PIN6
 #define KEYPAD_R2_PIN  DIO_PIN5
 #define KEYPAD_R3_PIN  DIO_PIN4       
 
 #define KEYPAD_C0_PIN DIO_PIN6
 #define KEYPAD_C1_PIN DIO_PIN5
 #define KEYPAD_C2_PIN DIO_PIN4
 #define KEYPAD_C3_PIN DIO_PIN3
  


#endif