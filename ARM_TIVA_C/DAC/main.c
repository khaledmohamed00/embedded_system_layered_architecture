#include <bsp.h>

int main(void){
PLL_Init();          // bus clock at 80 MHz

Switch_DAC_Init();       // Port F is onboard switches, LEDs, profiling

//Sound_Init(50000);   // initialize SysTick timer, 1.6kHz

 while(1){

         }
}

