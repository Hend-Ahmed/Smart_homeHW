#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"


void ADC_vidInit
(
	void
)
{
	/* !Comment: AVCC with external capacitor ar AREF pin */
	SET_BIT(ADMUX, 6);
	CLR_BIT(ADMUX, 7);
	
	/* !Comment: ADC Left Adjust Result */
	SET_BIT(ADMUX, 5);
	
	/* !Comment: ADC Prescaler Selections 128 */
	SET_BIT(ADCSRA, 0);
	SET_BIT(ADCSRA, 1);
	SET_BIT(ADCSRA, 2);
	
	/* !Comment: ADC Enable */
	SET_BIT(ADCSRA, 7);
	
}

uint8 ADC_u8ReadChannel
(
	uint8 u8ChannelId
)
{
	/* !Comment: Channel Selection */
	ADMUX &= 0b11100000;                    //To clear last 5 bits and keep first 3 bits which are used in init
	ADMUX |= u8ChannelId;
	
	/* !Comment: ADC Start Conversion */
	SET_BIT(ADCSRA, 6);
	
	/* !Comment: ADC Interrupt Flag */
	while(GET_BIT(ADCSRA, 4) == 0);
	
	/* !Comment: ADIF is cleared by writing a logical one to the flag */
	SET_BIT(ADCSRA, 4);
	
	/* !Comment: Retrun ADC Output Value */
	return ADCH;
}

