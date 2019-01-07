#include <bsp.h>

unsigned long H,L;
int main(void){
  __disable_irq();  // disable interrupts while initializing
  PLL_Init();           // bus clock at 80 MHz

  Switch_Init();        // arm PF4, PF0 for falling edge interrupts
  Motor_Init();         // output from PA5, SysTick interrupts
  __enable_irq();   // enable after all initialization are done
  while(1){ // main program is free to perform other tasks
    __WFI(); // low power mode
  }
}

