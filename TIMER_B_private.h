#ifndef _TIMER_B_PRIVATE_H_
#define _TIMER_B_PRIVATE_H_

#define TCCR1A      *((uint8*)0x4Fu)
#define TCCR1B      *((uint8*)0x4Eu)
#define TCNT1       *((uint16*)0x4Cu)
#define OCR1A       *((uint16*)0x4Au)
#define OCR1B       *((uint16*)0x48u)
#define ICR1        *((uint16*)0x46u)
#define TIMSK       *((uint8*)0x59u)
#define TIFR        *((uint8*)0x58u)

#endif