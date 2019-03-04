#include"STD_TYPES.h"
#include<avr/io.h>
#include"scheduler_init.h"

void task0_led_toggle(void){
PORTC^=(1<<0);


}


void task1_led_toggle(void){
PORTC^=(1<<1);

	
}

void task2_led_toggle(void){
PORTC^=(1<<2);

	
}



int main(void){
DDRC=0xff;

scheduler_intialize();
task_create(task0_led_toggle,5,Running);
task_create(task1_led_toggle,15,Running);
task_create(task2_led_toggle,20,Running);
scheduler_start();



while(1){



}


}

