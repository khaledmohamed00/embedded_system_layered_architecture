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

 void calculate_Duty_Cycle_Freq(u16 *duty_cycle ){
u16 a,b,c;
//,high,period;
        TCCR1A = 0;
        TCNT1=0;
		TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag) flag */

		//TCCR1B = 0x41;  	/* Rising edge, no prescaler */
		TCCR1B|=(1<<CS10)|(1<<ICES1);
		while ((TIFR&(1<<ICF1)) == 0);
		a = ICR1;  		/* Take value of capture register */
		TIFR |= (1<<ICF1);  	/* Clear ICF flag */
		
		//TCCR1B = 0x01;  	/* Falling edge, no prescaler */
		TCCR1B &=~(1<<ICES1);
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;  		/* Take value of capture register */
		TIFR |= (1<<ICF1);  	/* Clear ICF flag */
		
		//TCCR1B = 0x41;  	/* Rising edge, no prescaler */
		TCCR1B|=(1<<ICES1);
		while ((TIFR&(1<<ICF1)) == 0);
		c = ICR1;  		/* Take value of capture register */
		TIFR |= (1<<ICF1);  	/* Clear ICF flag */

		TCCR1B = 0;  		/* Stop the timer */
		
		if(a<b && b<c)  	/* Check for valid condition, 
					to avoid timer overflow reading */
		{
			 u16 High=b-a;
			 u16 Period=c-a;
			
			u16 Duty_cycle=(((float)High/(float)Period)*100);
			//LCD_write_int(Duty_cycle);
			*duty_cycle=Duty_cycle;
			
			
		}
		
		else
	 {
	 	
		}


}

int main (void){
DDRD|=(1<<0);
 u16 *duty_cycle;	
 init_LCD();
 init_Timer0PWM_OC0(128);
 ADC_Init();

	while(1)
	 {OCR0=ADCu16_Read(3);

       calculate_Duty_Cycle_Freq(duty_cycle);
	   LCD_write_int(*duty_cycle);
	   //LCD_vidWriteU16(*duty_cycle);
	   
	}

}

