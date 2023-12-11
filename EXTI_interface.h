#ifndef _EXTI_INTERFACE_H_
#define _EXTI_INTERFACE_H_

#define FallingEdge        0u    
#define RISING_EDGE        1u
#define ON_CHANGE          2u 
#define LOW_LEVEL          3u

#define INT0               0u
#define INT1               1u
#define INT2               2u


void EXTI_vidInterruptControl
(
	uint8 u8IntNumber,
	uint8 u8SenseMode
);

void EXTI_vidSetCallback 
(
	void (*ptr)(void)
);

#endif