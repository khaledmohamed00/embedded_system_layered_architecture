
#include"STD_TYPES.h"
#include<avr/io.h>
#include <avr/interrupt.h>
#include"Timer0_init.h"
#include"scheduler_config.h"


volatile u16 OVF_counts;
volatile u16 count=0;

void (*ptr_ISR)(void);



void init_Timer0_OVF(void)
{

TCCR0=(1<<CS01);
TIMSK=(1<<TOIE0);

}


void set_ISR_callback(void (*ptr_fun)(void)){

ptr_ISR=ptr_fun;

}

void no_of_counts(void){
double time_of_OVF=(double)4/15625.0;
 OVF_counts=(u16)(((double)scheduler_tick_time_ms/1000.0)/time_of_OVF);
}


ISR(TIMER0_OVF_vect){
 count++;
 if(count==OVF_counts)
 {
scheduler();
count=0;
}

}