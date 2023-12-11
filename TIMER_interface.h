#ifndef _TIMER_INTERFACE_H_
#define _TIMER_INTERFACE_H_

void vidDelay_ms(uint16 u8Delay);
void TIMER_vidSyncDelayMilliSecond(void);
void TIMER_vidSyncDelaySecond(void);
void TIMER_PWMInit(void);
void (*pvFunc_Callback)(void);
void TIMER_Init(void);
void TIMER0_vidSetCallBack(void (*ptr)(void));
void __vector_11 (void) __attribute__((signal));

#endif