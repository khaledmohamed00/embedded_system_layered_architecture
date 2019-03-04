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
			*duty_cycle=Duty_cycle;
			
			
		}
		
		else
	 {
		}


}
volatile u8 state=0;
volatile u16 a,b,c;

int main (void){
//unsigned int a,b,c,high,period;
DDRD|=(1<<0);
 u16 *duty_cycle;	
 init_LCD();
 init_Timer0PWM_OC0(128);
 ADC_Init();
TCCR1A = 0;
TCNT1=0;
TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag) flag */

		//TCCR1B = 0x41;  	/* Rising edge, no prescaler */
TCCR1B|=(1<<CS10)|(1<<ICES1);
	//PORTD = 0xFF;			/* Turn ON pull-up resistor */
TIMSK|=(1<<TICIE1);
sei();	
	while(1)
	 {OCR0=ADCu16_Read(3);

       
/********************************/

// u16 a,b,c,high,period;
//         TCCR1A = 0;
//         TCNT1=0;
// 		TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag) flag */

// 		TCCR1B = 0x41;  	/* Rising edge, no prescaler */
// 		//TCCR1B|=(1<<CS10)|(1<<ICES1);
// 		while ((TIFR&(1<<ICF1)) == 0);
// 		a = ICR1;  		/* Take value of capture register */
// 		TIFR |= (1<<ICF1);  	/* Clear ICF flag */
		
// 		TCCR1B = 0x01;  	/* Falling edge, no prescaler */
// 		//TCCR1B &=~(1<<ICES1);
// 		while ((TIFR&(1<<ICF1)) == 0);
// 		b = ICR1;  		/* Take value of capture register */
// 		TIFR |= (1<<ICF1);  	/* Clear ICF flag */
		
// 		TCCR1B = 0x41;  	 Rising edge, no prescaler 
// 		//TCCR1B|=(1<<ICES1);
// 		while ((TIFR&(1<<ICF1)) == 0);
// 		c = ICR1;  		/* Take value of capture register */
// 		TIFR |= (1<<ICF1);  	/* Clear ICF flag */

// 		TCCR1B = 0;  		/* Stop the timer */
		
// 		if(a<b && b<c)  	/* Check for valid condition, 
// 					to avoid timer overflow reading */
// 		{
// 			high=b-a;
// 			period=c-a;
			
// 			 freq= F_CPU/period;/* Calculate frequency */

// 						/* Calculate duty cycle */
//              duty_cycle =((float) high /(float)period)*100;			
			
			
// 		}
		
// 		else
// 		{
			
//          duty_cycle=0;
//          freq=0;
// 		}


/********************************/
       
            if(state==3){
            cli();
             state=0;
            if(a<b && b<c) {
           
            
	 		 u16 on_time=b-a;
	 		 u16 period=c-a;
	 		 u16 d=((float)on_time/period)*100;
	 		 u16 f=F_CPU/period;
	 		 LCD_write_int(d);
	 		 LCD_write_int(f);

	 		

	 		_delay_ms(100);

	 		LCD_cmd(0x01);
	 	}else{
	 		            TOG_BIT(PORTD,0);

	 	}
	 	TCNT1=0;
	 		sei();
                         }
	 	}

	   // }
	
	}


ISR(TIMER1_CAPT_vect){
if(state==0){
//TCNT1=0;
a=ICR1;

state++;
TCCR1B &=~(1<<ICES1);

}
else if(state==1){
b=ICR1;

state++;

TCCR1B |=(1<<ICES1);
}
else if(state==2){
c=ICR1;
state++;
//TCCR1B &=~(1<<ICES1);

}


}

