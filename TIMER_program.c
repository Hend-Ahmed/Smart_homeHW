#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER_private.h"
#include "TIMER_interface.h"

void (*pvFunc_Callback)(void);

void vidDelay_ms(uint16 u8Delay)
{
	uint16 u8Counter;
	for(u8Counter = 0; u8Counter < u8Delay; u8Counter++)
	{
		TIMER_vidSyncDelayMilliSecond();
	}
}

void TIMER_vidSyncDelayMilliSecond(void)
{
	/*!Comment: TIMER0 Normal mode*/
	CLR_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	
	/*!Comment: Preload value in timer register*/
	TCNT0 = 48;
	
	/*!Comment: Prescaler 8*/
	CLR_BIT(TCCR0,2);
	SET_BIT(TCCR0,1);
	CLR_BIT(TCCR0,0);
	
	/*!Comment: overflow 8 times*/
	uint8 LocalCounter;
	for(LocalCounter = 0; LocalCounter<8; LocalCounter++)
	{
		/* !Comment: waiting for overflow*/
		while(GET_BIT(TIFR,0)==0);
		/* !Comment: clearing overflow flag*/
		SET_BIT(TIFR,0);
	}
}

void TIMER_vidSyncDelaySecond(void)
{
	/*!Comment: TIMER0 Normal mode*/
	CLR_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	
	/*!Comment: Preload value in timer register*/
	TCNT0 = 112;
	
	/*!Comment: Prescaler 64*/
	CLR_BIT(TCCR0,2);
	SET_BIT(TCCR0,1);
	SET_BIT(TCCR0,0);
	
	/*!Comment: overflow 977 times*/
	uint16 localCounter = 0u;
	for(localCounter=0 ; localCounter<977 ; localCounter++)
	{
		/* !Comment: waiting for overflow*/
		while(GET_BIT(TIFR,0)==0);
		/* !Comment: clearing overflow flag*/
		SET_BIT(TIFR,0);
	}
}

void TIMER_PWMInit(void)
{
	/*!Comment: TIMER0 Fast PWM*/
	SET_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);
	
	/*!Comment: Non-Inverting Mode*/
	SET_BIT(TCCR0, 5);
	CLR_BIT(TCCR0, 4);
	
	/*!Comment: Set OCR0 pin output */
	DIO_udtSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);
}

void TIMER_Init(void)
{
	/*!Comment: TIMER0 Normal mode*/
	CLR_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	
	/*!Comment: Preload value in timer register*/
	TCNT0 = 112;
	
	/*!Comment: Prescaler 64*/
	CLR_BIT(TCCR0,2);
	SET_BIT(TCCR0,1);
	SET_BIT(TCCR0,0);
	
	/*!Comment: enable timer0 interrupt*/
	SET_BIT(TIMSK,0);
	
}


void TIMER0_vidSetCallBack(void (*ptr)(void) )
{
	pvFunc_Callback = ptr ; 
}

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	pvFunc_Callback();
}




