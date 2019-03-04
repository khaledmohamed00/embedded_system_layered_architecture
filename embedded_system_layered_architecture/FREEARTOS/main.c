
#include "STD_TYPES.h"
#include <avr/io.h>
#include "FreeRTOS.h"
#include "semphr.h"
//#include "LCD.h"
#include "task.h"
#include "queue.h"

xSemaphoreHandle Push_Semaphore;
xQueueHandle xQueue;

//================= [Tasks] ===============
// void LCD_Write1( void *pvParameters)
// {
// 	portTickType StartTime = xTaskGetTickCount();
// 		while(1)
// 	{

// 		LCD_voidDisplayData('W');
// 		vTaskDelayUntil(&StartTime,500); //OS Delay
// 	}
// }
// //================= [Tasks] ===============
// void Blink_500ms_task( void *pvParameters)
// {
// 	DDRA |=(1<<0); //PA.0 is output
	
// 	while(1)
// 	{
// 		xSemaphoreTake(Push_Semaphore,200);
		
// 		PORTA ^= (1<<0); //toggle PA.0
// 		xSemaphoreGive(Push_Semaphore);
// 		vTaskDelay(500); //OS Delay
// 	}
// }
// //--------------------------------------------------
// void Blink_1000ms_task( void *pvParameters)
// {
// 	DDRB |=(1<<0); //PB.0 is output

// 	while(1)
// 	{

// 		PORTB ^= (1<<0); //toggle PB.0
// 		vTaskDelay(1000); //OS Delay
// 	}
// }
// //---------------------------------------------
void Blink_1500ms_task( void *pvParameters)
{u8 lReceivedValue;
u8 xStatus;
//const u8 xTicksToWait = pdMS_TO_TICKS( 100 );
	DDRA |=(1<<0); //PA.0 is output

	while(1)
	{xStatus = xQueueReceive( xQueue, &lReceivedValue, 50 );
     uart_send_char(lReceivedValue);
		PORTA ^= (1<<0); //toggle PA.0
		vTaskDelay(1500); //OS Delay
	}
}
//--------------------------------------------------
void Blink_2000ms_task( void *pvParameters)
{u8 xStatus;
 u8	lValueToSend='a';
	DDRA |=(1<<0); //PB.0 is output
	
	while(1)
	{xStatus = xQueueSendToBack( xQueue, &lValueToSend, 0 );
		
		PORTA ^= (1<<0); //toggle PB.0
		vTaskDelay(2000); //OS Delay
	}
}


//================= [Main] ====================
//#include <avr/io.h>
int main(void)
{//DDRA =0xff;
 //PORTA=0xff;	
	uart_init();
    //void uart_send_char(u8 c);
    //u8 uart_receive_char(void);
	xQueue = xQueueCreate( 5, sizeof(u8) );
	
	// Create Tasks
	//xTaskCreate( Blink_500ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	//xTaskCreate( Blink_1000ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( Blink_1500ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( Blink_2000ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 3, NULL );

	vSemaphoreCreateBinary(Push_Semaphore);

	// Start FreeRTOS
	vTaskStartScheduler();
	
}

