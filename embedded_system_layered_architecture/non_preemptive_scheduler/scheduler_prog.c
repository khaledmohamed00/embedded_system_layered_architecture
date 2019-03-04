#include"STD_TYPES.h"
#include"scheduler_init.h"
#include <avr/interrupt.h>
#include "Timer0_init.h"
#include"scheduler_config.h"








typedef struct{
u8 periodicity;
state task_state;
ptr ptr_func;
u8 task_time;
}TCB; 

TCB task_arr[no_of_tasks];


void scheduler_intialize(void){
init_Timer0_OVF();
no_of_counts();
set_ISR_callback(&scheduler);


}

void scheduler_start(void){

sei();

}


void task_create(ptr ptr_func_copy,u8 u8periodicity_copy,state enum_process_state_copy){
static u8 no_of_task=0;
task_arr[no_of_task].periodicity=u8periodicity_copy;
task_arr[no_of_task].task_state=enum_process_state_copy;
task_arr[no_of_task].ptr_func=ptr_func_copy;
task_arr[no_of_task].task_time=u8periodicity_copy;
no_of_task++;


}






void scheduler(void){

cli();
int i;
for(i=0;i<no_of_tasks;i++){
if(task_arr[i].task_state==Running){
if(task_arr[i].task_time>0)
{task_arr[i].task_time--;
}
if(task_arr[i].task_time==0){

	task_arr[i].ptr_func();
	task_arr[i].task_time=task_arr[i].periodicity;
}

}


}
sei();

}
