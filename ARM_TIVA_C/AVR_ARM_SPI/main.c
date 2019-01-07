#include <spi.h>
#include "TM4C123GH6PM.h"
//SPI COMMUNICATION
uint8_t leds = 0x00;


int main()
{
  spi_init();

  SYSCTL->RCGCGPIO |= (1<<5); // enable clock on PortF
  GPIOF->DIR = (1<<1)|(1<<2)|(1<<3);  // make LED pins (PF1, PF2, and PF3) outputs
  GPIOF->DEN = (1<<1)|(1<<2)|(1<<3); // enable digital function on LED pins
  GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3)); // turn off leds

  while(1)
  {
    //GPIOB->DATA &= ~(1<<5); // SS/CS Low, begin transmission
   // GPIOB->DATA |= (1<<5); // SS/CS High, end transmission

    for(int i=0;i<1000000;i++);
    read_writeSPI(0b00001111);
    //writeSPI(0b00000011);
    for(int i=0;i<1000000;i++);
    read_writeSPI(0b00000000);

   // writeSPI(0b00000000);



  }

  return 0;
}
