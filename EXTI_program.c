#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

void (*EXTI_globalptr) 
(
	void
);

void EXTI_vidInterruptControl
(
	uint8 u8IntNumber,
	uint8 u8SenseMode
)
{
	switch(u8IntNumber)
	{
		case INT0:
				if(u8SenseMode == FallingEdge)
				{
					SET_BIT(MCUCR, 1);
					CLR_BIT(MCUCR, 0);
				}
				else if(u8SenseMode == RISING_EDGE)
				{
					SET_BIT(MCUCR, 1);
					SET_BIT(MCUCR, 0);
				}
				else if(u8SenseMode == ON_CHANGE)
				{
					CLR_BIT(MCUCR, 1);
					SET_BIT(MCUCR, 0);

				}
				else if(u8SenseMode == LOW_LEVEL)
				{
					CLR_BIT(MCUCR, 1);
					CLR_BIT(MCUCR, 0);
				}
				
				/* !Comment: Enable INT0 */
				SET_BIT(GICR, 6);
				break;
		case INT1:
				if(u8SenseMode == FallingEdge)
				{
					SET_BIT(MCUCR, 3);
					CLR_BIT(MCUCR, 2);
				}
				else if(u8SenseMode == RISING_EDGE)
				{
					SET_BIT(MCUCR, 3);
					SET_BIT(MCUCR, 2);
				}
				else if(u8SenseMode == ON_CHANGE)
				{
					CLR_BIT(MCUCR, 3);
					SET_BIT(MCUCR, 2);

				}
				else if(u8SenseMode == LOW_LEVEL)
				{
					CLR_BIT(MCUCR, 3);
					CLR_BIT(MCUCR, 2);
				}
				
				/* !Comment: Enable INT1 */
				SET_BIT(GICR, 7);
				break;
		
		case INT2:
				if(u8SenseMode == FallingEdge)
				{
					CLR_BIT(MCUCSR, 6);
				}
				else if(u8SenseMode == RISING_EDGE)
				{
					SET_BIT(MCUCSR, 6);
				}
				/* !Comment: Enable INT1 */
				SET_BIT(GICR, 5);				
				break;
		default:
				break;
	}
}

void EXTI_vidSetCallback
(
	void(*ptr)(void)
)
{
	EXTI_globalptr = ptr ;
}

void __vector_1 (void)  __attribute__ ((signal));
void __vector_1 (void) 
{
	EXTI_globalptr();
}

