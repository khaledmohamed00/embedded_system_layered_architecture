#include "i2c.h"
#include "TM4C123GH6PM.h"
//I2C COMMUNICATION MCP23008

uint8_t leds = 0x00;


int main()
{
  i2c_init();

  //1 byte must be sent
  setSlaveAddress(0x20); //last 7 bits (7-1)
  setRW(0); //first bit (0)

  //writeByte(BYTE ONE, BYTE TWO)

  //send IODIR register address
  writeByte(0xff, (1<<0)|(1<<1)); //BYTE TWO: conditions = RUN and START
 // writeByte(0xff, (1<<0)|(1<<1)|(1<<2)); //BYTE TWO: conditions = RUN and START,stop

  //send IODIR value to make GPIO pins outputs
  writeByte(0xff, (1<<0)|(1<<2)); //BTYE TWO: conditions = RUN, STOP

  while(1)
  {//send GPIO register address
    //writeByte(0x09, (1<<0)|(1<<1));
   //send GPIO value
    //writeByte(leds++, (1<<0)|(1<<2));

    //for(int i = 0; i < 100000; i++){};

  }


  return 0;
}
