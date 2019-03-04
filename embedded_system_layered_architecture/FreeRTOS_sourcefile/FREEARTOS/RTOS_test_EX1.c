/*
 * RTOS_test_EX1.c
 *
 * In this  exercise, we have two tasks. First task blinks a LED every 200 msec and the other one blinks a LED every 1000 msec
 * The two tasks run in parallel.
 *
 *  Author: Nael
 */ 
#include "STD_Types.h"
#include <avr/io.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "LCD.h"
#include "task.h"

xSemaphoreHandle Push_Semaphore;

//================= [Tasks] ===============
void LCD_Write1( void *pvParameters)
{
	portTickType StartTime = xTaskGetTickCount();
		while(1)
	{

		LCD_voidDisplayData('W');
		vTaskDelayUntil(&StartTime,500); //OS Delay
	}
}
//================= [Tasks] ===============
void Blink_500ms_task( void *pvParameters)
{
	DDRA |=(1<<0); //PA.0 is output
	
	while(1)
	{
		xSemaphoreTake(Push_Semaphore,200);
		
		PORTA ^= (1<<0); //toggle PA.0
		xSemaphoreGive(Push_Semaphore);
		vTaskDelay(500); //OS Delay
	}
}
//--------------------------------------------------
void Blink_1000ms_task( void *pvParameters)
{
	DDRB |=(1<<0); //PB.0 is output

	while(1)
	{

		PORTB ^= (1<<0); //toggle PB.0
		vTaskDelay(1000); //OS Delay
	}
}
//---------------------------------------------
void Blink_1500ms_task( void *pvParameters)
{
	DDRC |=(1<<0); //PA.0 is output

	while(1)
	{

		PORTC ^= (1<<0); //toggle PA.0
		vTaskDelay(1500); //OS Delay
	}
}
//--------------------------------------------------
void Blink_2000ms_task( void *pvParameters)
{
	DDRD |=(1<<0); //PB.0 is output
	
	while(1)
	{
		
		PORTD ^= (1<<0); //toggle PB.0
		vTaskDelay(2000); //OS Delay
	}
}


//================= [Main] ====================
#include <avr/io.h>

int main(void)
{
	// Create Tasks
	xTaskCreate( Blink_500ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( Blink_1000ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( Blink_1500ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( Blink_2000ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );

	vSemaphoreCreateBinary(Push_Semaphore);

	// Start FreeRTOS
	vTaskStartScheduler();
	
}
