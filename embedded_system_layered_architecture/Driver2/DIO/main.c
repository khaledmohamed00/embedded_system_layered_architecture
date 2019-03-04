#include "STD_TYPES.h"
//#include"DIO_int.h"
#include "LCD_int.h"
#include "KPD_interface.h"
#include "ADC_int.h"
#include <avr/io.h>
int main(void){






init_LCD();
ADC_Init();
DDRB=0x0f;
PORTB=0xff;
DDRA&=~(1<<7);
u16 digital_value=ADCu16_Read(7);
u16 analog_value=(u16)((u32)digital_value*5000/1024);
LCD_write_int(analog_value);
while(1){

//u8 key=KPD_u8GetPressedKey();


//LCD_write(key);

}



return 0;
}
