#include <bsp.h>
unsigned long adc;
int main(void){
    ADC0_InitSWTriggerSeq3_Ch9();
 while(1){
  adc=ADC0_InSeq3();
         }
}

