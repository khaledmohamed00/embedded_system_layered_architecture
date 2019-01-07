
#include <bsp.h>
#include <FreeRTOS.h>
#include<task.h>
#include <queue.h>
unsigned long In;  // input from PF4

unsigned long Out; // output to PF2 (blue LED)

//   Function Prototypes


// 3. Subroutines Section

// MAIN: Mandatory for a C Program to be executable

int main(void){    // initialize PF0 and PF4 and make them inputs
  PLL_Init();
  PortF_Init();    // make PF3-1 out (PF3-1 built-in LEDs)
  SysTick_CMSIS_Init();
  __enable_irq();
  //xTaskCreate(PortF_Init,(unsigned char)'PortF_Init',1024,1,NULL);
  //vTaskStartScheduler();
  while(1){

     // GPIO_PORTF_DATA_R^=(1<<LED_GREEN);

      // SysTick_Wait10ms(10);
      //SysTick_Handler();

    /*In = GPIO_PORTF_DATA_R&0x10;   // read PF4 into Sw1

    In = In>>2;                    // shift into position PF2

    Out = GPIO_PORTF_DATA_R;

    Out = Out&0xFB;

    Out = Out|In;

    GPIO_PORTF_DATA_R = Out;        // output
   */
  }

}


