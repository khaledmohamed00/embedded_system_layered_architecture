/*
 * main.c
 *
 *  Created on: Sep 14, 2018
 *      Author: hp
 */
#define F_CPU 8000000ul
#include"STD_TYPES.h"
#include <avr/io.h>
#include <util/delay.h>

//#include "types.h"
//#include "Dio_int.h"
#include "ADC_int.h"
#include "LCD_int.h"


int main(void)
{
	ADC_Init();		/* Initialize ADC */
	init_LCD();
	DDRD |= (1<<PD5);	/* Make OC1A pin as output */ 
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */

	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	while(1)
	{
	   OCR1A = 65 + (ADCu16_Read(3)/4.35);
	   LCD_write_int(65 + (ADCu16_Read(3)/4.35));
	   /* Read ADC channel 0 and make count in between 65-300 i.e. 0.5-2.4 mSec duty cycle variation */
	}
}



// int main(void)
// {
// 	u16 u16_ADCValue =0;
//     init_LCD();
// 	ADC_Init();

//    //Configure TIMER1
//    TCCR1A|=/*(0<<COM1A0)|*/(1<<COM1A1)|(1<<WGM11)|(0<<WGM10);        //NON Inverted Fast PWM
//    TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10)|(0<<CS12); //PRESCALER=64 MODE 14(FAST PWM)

//    ICR1=2499;  //fPWM=50Hz (Period = 20ms Standard).
//    DDRD=(1<<PD4)|(1<<PD5);   //PWM Pins as Out

//    while(1)
//    {OCR1A = 65 + (ADCu16_Read(3)/4.35);
// 	  /*u16_ADCValue= ADCu16_Read(3);
// 	  //u16_ADCValue /= 3;
//       OCR1A = u16_ADCValue;   //0 degree*/
//       LCD_write_int(u16_ADCValue);
//       _delay_ms (100);
//      LCD_cmd(0x01);

//    }
// }


// int main(void)
// {u16 u16_ADCValue =0;
// 	DDRD |= (1<<PD5);	/* Make OC1A pin as output */ 
// 	TCNT1 = 0;		/* Set timer1 count zero */
// 	ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */
//     init_LCD();
// 	ADC_Init();

// 	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
// 	TCCR1A = (1<<WGM11)|(1<<COM1A1);
// 	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
// 	while(1)
// 	{u16_ADCValue= ADCu16_Read(3);
// 		OCR1A = u16_ADCValue;	/* Set servo shaft at -90° position */
// 		LCD_write_int(u16_ADCValue);
// 		_delay_ms(100);
// 		LCD_cmd(0x01);
// 		// OCR1A = 175;	/* Set servo shaft at 0° position */
// 		// _delay_ms(1500);
// 		// OCR1A = 300;	/* Set servo at +90° position */
// 		// _delay_ms(1500);
// 	}
// }
