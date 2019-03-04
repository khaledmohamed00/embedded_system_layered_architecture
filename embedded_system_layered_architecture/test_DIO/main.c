#define F_CPU 8000000ul
#include "STD_TYPES.h"
#include "DIO_int.h"
#include <util/delay.h>
u8 seven_segment[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x6f};
int main(void){

DIO_SetPortDirection(PORTA,0xff);
DIO_SetPortDirection(PORTB,0x07);
//LCD_DDR=0xff;
//ctrl_DDR=0x07;
init_LCD();
_delay_ms(50);
LCD_write('A');
while(1){
/*u8 i=0;
for(i=0;i<10;i++ ){
DIO_SetPortValue(PORTA,seven_segment[i]);
_delay_ms(1000);

}*/

}


}
