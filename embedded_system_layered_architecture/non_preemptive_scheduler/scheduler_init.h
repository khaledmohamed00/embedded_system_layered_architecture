#ifndef _SCHEDULER_INIT_H
#define _SCHEDULER_INIT_H

typedef enum {
	Running,
	Blocked

 }state;
typedef void (*ptr)(void);
void task_create(ptr ptr_func_copy,u8 u8periodicity_copy,state enum_process_state_copy);
void scheduler(void);
void scheduler_intialize(void);
void scheduler_start(void);


#endif