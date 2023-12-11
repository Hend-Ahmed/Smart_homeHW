#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TIMER_B_interface.h"
#include "TIMER_B_config.h"
#include "TIMER_B_private.h"
#include "DIO_interface.h"
#include <util/delay.h>


void TIMER1_vidInit(void)
{
	  SET_BIT(TCCR1A, 5);
      SET_BIT(TCCR1A, 1);
	  
	  SET_BIT(TCCR1B, 4);
	  SET_BIT(TCCR1B, 3);
	  SET_BIT(TCCR1B, 1);

     ICR1 = 39999;
	 DIO_udtSetPinDirection(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);
	
}

uint8 servo_rotate(void)
{
	OCR1B = 1000;
	vidDelay_ms(2000);
	
	OCR1B = 4000;
	vidDelay_ms(1000);
	
	OCR1B = 0;
	
	return 0;
}

void TIMER_B_PWMInit(void)
{
	/*!Comment: TIMER1_MODE_OF_OPERATION --> Mode 14:Fast Mode*/
	CLR_BIT(TCCR1A, 0);
	SET_BIT(TCCR1A, 1);
	SET_BIT(TCCR1B, 3);
	SET_BIT(TCCR1B, 4);
	
	TCNT1 = 0;
	/*!Comment: Clear on Comp Set on top (NON-INVERTING)*/
	SET_BIT(TCCR1A, 7);
	CLR_BIT(TCCR1A, 6);
	
	/*!Comment: Top Value */
	ICR1 = 255;
	/*!Comment: Prescaler CLK/8 */
	CLR_BIT(TCCR1B, 0);
	SET_BIT(TCCR1B, 1);
	CLR_BIT(TCCR1B, 2);
	
	/*!Comment: Set OCR1A pin output*/
	DIO_udtSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);
}
