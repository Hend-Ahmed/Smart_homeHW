#include "BIT_MATH.h"
#include "STD_TYPES.h"

#define F_CPU 16000000UL
#define SCL_CLK 400000UL

#include <util/delay.h>

#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "Smart_interface.h"


extern uint8 Admin_Flag;

int main ()
{
	/*!Comment: Initialization Of UART, LCD, KEYPAD & I2C */
	UART_init();
	LCD_vidInit();
	KEYPAD_vid_Init ();
	I2C_Init();
	
	/*!Comment: Function to check & store users added every start of the system (Power Off) */
	vid_If_User_Added();
	
	/*!Comment: EXINT INTIALIZATION */
	GIE_vidEnableGlobalInterrupt();
	EXTI_vidSetCallback(KeyPadSelect);
	EXTI_vidInterruptControl(INT0,FallingEdge);
	
	/*!Comment: BUZZER PIN */
	DIO_udtSetPinDirection(DIO_PORTA, DIO_PIN3, DIO_OUTPUT);
	
	/*!Comment: DC MOTOR PIN*/
	DIO_udtSetPinDirection(DIO_PORTD, DIO_PIN7, DIO_OUTPUT);
	DIO_udtSetPinValue(DIO_PORTD, DIO_PIN7, DIO_HIGH);
	
	/*!Comment: LEDs Pins */
	DIO_udtSetPinDirection(DIO_PORTD, DIO_PIN3, DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTD, DIO_PIN6, DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTB, DIO_PIN0, DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTC, DIO_PIN2, DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTC, DIO_PIN7, DIO_OUTPUT);

	while (1)
	{
		 LCD_Clear();
		 LCD_vidProgram();
		 LCD_Clear();
	}
}