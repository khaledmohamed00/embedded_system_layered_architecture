#ifndef _TIMER0_INIT_h
#define _TIMER0_INIT_h
#define time_in_ms 100
void init_Timer0_OVF(void);
void set_ISR_callback(void (*ptr_fun)(void));
void no_of_counts(void);


#endif