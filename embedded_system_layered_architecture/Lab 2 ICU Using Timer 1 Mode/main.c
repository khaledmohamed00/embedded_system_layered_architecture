/*
 * main.c
 *
 *  Created on: Mar 25, 2018
 *      Author: Ahmed
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "Log_int.h"
#include "LCD_interface.h"
#include "TIM0_int.h"
#include "avr/io.h"

volatile static u8 flag = 0;
volatile static u8 x,y,Duty_Cycle;
volatile static u16 temp1, temp2, temp3;

void ICU_Init(void)
{
	TCCR1A = 0;
	TCCR1B = 0b01000001;
	/* Enable Interrupt */
	SET_BIT(TIMSK,5);

	/* Clear Flag */
	SET_BIT(TIFR,5);
}



void __vector_6 (void) __attribute__((signal,used));
void __vector_6 (void)
{
	if (flag == 0)
	{
		x = ICR1L;
		y = ICR1H;
		temp1 = x |(y<<8);

		flag  = 1;
	}

	else if (flag == 1)
	{
		/* Falling Edge */
		CLR_BIT(TCCR1B,6);

		x = ICR1L;
		y = ICR1H;
		temp2 = x |(y<<8);

		flag = 2;


	}

	else if (flag == 2)
	{
		x = ICR1L;
		y = ICR1H;
		temp3 = x |(y<<8);

		flag = 3;
	}
}


void main(void)
{
	u16 period;
	u16 on_time;

	/* Initialize IO */
	/* DIO Initializations */
	/* PORT A as Output */
	DIO_SetPortDirection(xPORTA,0xFF);
	/* A0 and A1 and A2 as output */
	DIO_SetPinDirection (xPORTD,PIN0,OUTPUT);
	DIO_SetPinDirection (xPORTD,PIN1,OUTPUT);
	DIO_SetPinDirection (xPORTD,PIN2,OUTPUT);
	
	/* OC0 which is B3 to output */
	DIO_SetPinDirection (xPORTB,PIN3,OUTPUT);
	
	/* ICP1 which is D6 to input */
	DIO_SetPinDirection (xPORTD,PIN6,INPUT);
	
	/* LCD Initializations */
	LCD_voidInit();
	
	/* TIM 0 Initialize */
	TIM0_voidInitialize();

	/* 25 % PWM */
	TIM0_voidSetCompareVal(128);

	ICU_Init();

	/* Enable GIE */
	SET_BIT(SREG,7);

	/* Wait until ICU detects complete PWM */
	while (flag != 3);


	period  = temp2  - temp1;
	on_time = temp3  - temp2;
	Duty_Cycle = (on_time * 100) / period;

	/* Display data On LCD */
	Log_voidPrintString("Period = ");
	Log_voidPrintNumber(period);
	Log_voidPrintString("Count");

	LCD_voidGotoxy(2,1);
	Log_voidPrintString("Duty Cycle = ");
	Log_voidPrintNumber(Duty_Cycle);
	Log_voidPrintString("%");


	while(1)
	{

	}
}
