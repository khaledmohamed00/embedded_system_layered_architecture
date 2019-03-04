#define F_CPU 8000000ul
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include"ADC_int.h"
#include "LCD_int.h"
#include<util/delay.h>
#include<avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


void init_Timer0PWM_OC0(u8 ocro_value){
DDRB|=(1<<3);
TCCR0 |= (1<<WGM00)|(1<<WGM01)       // Start timer0 without
             |(1<<COM01)|(1<<CS00);
OCR0=ocro_value;
}


 void sense_control(u8 sense){

switch(sense){

	case 0://falling
	MCUCSR|=(1<<ISC01);
    MCUCSR &=~(1<<ISC00);
    break;
    
    case 1://rising
    MCUCSR|=(1<<ISC00)|(1<<ISC01);
    break;

}

}


void INTO_init(void){
GICR|=(1<<INT0);


}



void init_Timer1_Normal(){

	TCCR1B|=(1<<CS10);
	//TIMSK|=(1<<TOIE1);
}

void test(u16* ptr1,u16*ptr2){
*ptr1=5000;
*ptr2=6000;
}

volatile u8 flag=0;
volatile u8  state=0;
volatile u8  on_time=0;
volatile u16  period=0;
u8 count=0; 
char _number[20];
char _buffer[20];


int main(void){
u16* ptr1,u16*ptr2
DDRD|=(1<<0);
DDRD&=~(1<<2);
//PORTD&=~(1<<3);
//init_LCD();
uart_init();

ADC_Init();
INTO_init();
sense_control(1);
init_Timer0PWM_OC0(50);
init_Timer1_Normal();
sei();

//LCD_write_int(ADCu16_Read(3));
 

//sei();

while(1){

while(state!=3);
//while(flag!=2);
cli();

state=0;
// LCD_write_int(period);
// //LCD_write(' ');
// //LCD_write_int(on_time);


// _delay_ms(200);
// LCD_cmd(0x01);
// //OCR0=ADCu16_Read(3);
// flag=0;
dtostrf( (double)on_time, 5, 2, _number );                 //  Take values in buffer to send all parameters over USART 
sprintf(_buffer,"on_time=%s\r\n",_number);
USART_SendString(_buffer);
dtostrf( (double)period, 5, 2, _number );                 //  Take values in buffer to send all parameters over USART 
sprintf(_buffer,"period=%s\r\n",_number);
USART_SendString(_buffer);
//OCR0=ADCu16_Read(3);
sei();


	}
return 0;
}



ISR(INT0_vect){

switch(state){

	case 0:
     TCNT1=0;
     state++;
     sense_control(0);
	break;

	case 1:
    on_time=TCNT1;
    state++;
    sense_control(1);
    break;
 
   	case 2:
    period=TCNT1;
    state++;
    break;
}
/*if(flag==0){
     TCNT1=0;
//sense_control(0);

flag=1;

}else if(flag==1){
period=TCNT1;
flag=2;
//sense_control(1);

}*/

}
