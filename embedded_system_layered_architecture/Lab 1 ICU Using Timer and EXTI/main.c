#include "STD_TYPES.h"
#define F_CPU 12000000UL
#include "avr/delay.h"

#include "DIO_interface.h"
#include "TIM0_interface.h"
#include "TIM1_interface.h"
#include "LCD_interface.h"
#include "Log_interface.h"

void main(void)
{
	u16 Frequency = 0;
	u16 DutyCycle = 0;
	
	/* DIO Initializations */
	/* PORT D as Output */
	DIO_SetPortDirection(PORTA,0xFF);
	/* A0 and A1 and A2 as output */
	DIO_SetPinDirection (PORTD,PIN5,OUTPUT);
	DIO_SetPinDirection (PORTD,PIN6,OUTPUT);
	DIO_SetPinDirection (PORTD,PIN7,OUTPUT);
	
	/* OC0 which is B3 to output */
	DIO_SetPinDirection (PORTB,PIN3,OUTPUT);
	
	/* EXTI 0 which is D2 to input */
	DIO_SetPinDirection (PORTD,PIN2,INPUT);
	
	/* LCD Initializations */
	LCD_voidInit();
	
	/*
	LCD_voidGotoxy(1,1);
	Log_voidPrintString("Freq = ");
	LCD_voidGotoxy(1,13);
	Log_voidPrintString("Hz");
	
	LCD_voidGotoxy(2,1);
	Log_voidPrintString("Duty = ");
	LCD_voidGotoxy(2,13);
	Log_voidPrintString("%");
	*/
	
	/* Timer 0 initialize in Fast PWM */
	TIM0_initialize();
	
	/* Timer 1 initialization */
	TIM1_initialize();
	
	/* EXTI0 Initializations */
	EXTI0_Initialize();
	
	while(1)
	{
		EXTI0_GetIcuSignal(&Frequency,&DutyCycle);
		

		LCD_voidGotoxy(1,8);
		Log_voidPrintNumber(Frequency);
		LCD_voidGotoxy(2,8);
		Log_voidPrintNumber(DutyCycle);

		_delay_ms(500);


	}
	
}
