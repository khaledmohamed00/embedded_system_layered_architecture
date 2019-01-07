#include <spi.h>
#include "TM4C123GH6PM.h"
//SPI COMMUNICATION
uint8_t leds = 0x00;


int main()
{
  spi_init();
  /*writeSPI(0x40); //slave addrss. Here I also mention that I want to write
  writeSPI(0x00); //IODIR address
  writeSPI(0x00); //LEDs are off

  for(int i = 0; i < 60; i++);
  GPIOB->DATA |= (1<<5); // SS/CS high, end transmission
*/
  SYSCTL->RCGCGPIO |= (1<<5); // enable clock on PortF
  GPIOF->DIR = (1<<1)|(1<<2)|(1<<3);  // make LED pins (PF1, PF2, and PF3) outputs
  GPIOF->DEN = (1<<1)|(1<<2)|(1<<3); // enable digital function on LED pins
  GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3)); // turn off leds
  //GPIOB->DATA |= (1<<5); // SS/CS high, end transmission

  while(1)
  {
    /*GPIOB->DATA &= ~(1<<5); // SS/CS Low, begin transmission

    writeSPI(0x40); //slave addrss. Here I also mention that I want to write
    writeSPI(0x09); //GPIO address
    writeSPI(leds++); //set pins as outputs

    for(int i = 0; i < 60; i++);
    GPIOB->DATA |= (1<<5); // SS/CS High, end transmission

    for(int i = 0; i < 100000; i++);*/
     GPIOB->DATA &= ~(1<<5); // SS/CS Low, begin transmission

     for(int i = 0; i < 1000; i++);
      GPIOF->DATA=0;
      uint8_t data=read_writeSPI(0b00000111);
      GPIOB->DATA |= (1<<5); // SS/CS high, end transmission
      for(int i = 0; i < 1000; i++);

     //writeSPI(0b00000011);
   //  GPIOB->DATA |= (1<<5); // SS/CS high, end transmission

     // uint8_t data=read_writeSPI(0b00001110);
      //uint8_t data=readSPI();
     // GPIOF->DATA=data;
      /*for(int i = 0; i < 60; i++);
        GPIOB->DATA |= (1<<5); // SS/CS high, end transmission
      GPIOB->DATA &= ~(1<<5); // SS/CS Low, begin transmission
      writeSPI(0b00000011);*/
    // GPIOB->DATA &= ~(1<<5); // SS/CS Low, begin transmission

      //for(int i = 0; i < 1000000; i++);

     // writeSPI(0b00000000);
      //data=read_writeSPI(0b00000000);

  }

  return 0;
}
