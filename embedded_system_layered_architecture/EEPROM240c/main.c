#define F_CPU 8000000ul
#include<avr/io.h>
#include"eeprom.h"
#include<util/delay.h>
int main(void){
unsigned char *data;
DDRA=0xff;
//PORTA=0xff;
EEPROM_Init();
char flag_w=EEPROM_WriteByte(0x02,0x03);
_delay_ms(100);
char flag_r=EEPROM_ReadByte(0x02,data);
PORTA=*data;
//if(flag_r==1)
//PORTA=0xff;
while(1){



}


}
