#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include"spi.h"


int main (void)
{DDRC=0xff;
 char data;
 spi_slave_init();
  
    while(1)
    {
       
     PORTC =SPI_SlaveReceive();
  PORTC= spi_send_receive(0b11110000);
  //PORTC= spi_send_receive(3<<1);
  //SPI_MasterTransmit(3<<1); 
 }
}




