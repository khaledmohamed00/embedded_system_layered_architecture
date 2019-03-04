#define F_CPU 8000000ul
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include"ADC_int.h"
#include "LCD_int.h"
#include<util/delay.h>
#include<avr/io.h>
#include <avr/interrupt.h>
void init_Timer0PWM_OC0(u8 ocro_value){
DDRB|=(1<<3);
//TCCR0|=(1<<5)|(1<<6)|(1<<4)|(1<<3);
//TCCR0|=(1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<COM00);
 TCCR0 |= (1<<WGM00)|(1<<WGM01)       // Start timer0 without
             |(1<<COM01)|(1<<CS00);
OCR0=ocro_value;
//TCCR0|=(1<<CS00);
}
 void sense_control(u8 sense){
MCUCSR|=(1<<ISC10);
    //MCUCSR &=~(1<<ISC10);
/*switch(sense){

	case 0://falling
	MCUCSR|=(1<<ISC11);
    MCUCSR &=~(1<<ISC10);
    break;
    
    case 1://rising
    MCUCSR|=(1<<ISC10)|(1<<ISC11);
    break;

}*/	

}
void INTO_init(void){
GICR|=(1<<INT1);


}

void init_Timer1_Normal(){

	TCCR1B|=(1<<CS10);
	//TIMSK|=(1<<TOIE1);
}
volatile u8  state=0;
volatile u8  on_time=0;
volatile u8  period=0;
u8 count=0; 
int main(void){
DDRD|=(1<<0);
DDRD&=~(1<<3);
PORTD&=~(1<<3);
init_LCD();
ADC_Init();
INTO_init();
sense_control(0);
init_Timer0PWM_OC0(128);
init_Timer1_Normal();
sei();
//LCD_write('A');
//LCD_write_int(ADCu16_Read(3));
//init_Timer0_OC0();
 

while(state!=3);
cli();

//cli();
//if(state==3){
state=0;
LCD_write_int(period);
LCD_write_int(on_time);
//LCD_write('1');
//LCD_write('1');

//_delay_ms(100);
//LCD_cmd(0x01);
//}
//init_Timer0_OC0(ADCu16_Read(3));
//OCR0=ADCu16_Read(3);
sei();

while(1){

/*if(state==3){
cli();

//cli();
//if(state==3){
state=0;
//LCD_write_int(period);
LCD_write_int(on_time);
//LCD_write('1');
//LCD_write('1');

//_delay_ms(100);
LCD_cmd(0x01);
//}
//init_Timer0_OC0(ADCu16_Read(3));
OCR0=ADCu16_Read(3);
sei();

}*/


//_delay_ms(100);

// clear LCD
//_delay_ms(100);
//init_Timer0_OC0(ADCu16_Read(3));

	}
return 0;
}

ISR(INT1_vect){

switch(state){

	case 0:
     TCNT1=0;
     state++;
     //sense_control(0);
	break;

	case 1:
    on_time=TCNT1;
    state++;
    //sense_control(1);
    break;
 
   	case 2:
    period=TCNT1;
    state++;
    break;
}
//TOG_BIT(PORTD,0);
}
