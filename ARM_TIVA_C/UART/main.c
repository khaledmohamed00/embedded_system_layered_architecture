#include "uart.h"

unsigned char data;
int main(void){    // initialize PF0 and PF4 and make them inputs
    UART_Init();
  while(1){
      UART_OutChar('1');
      data=UART_InChar();
  }

}

