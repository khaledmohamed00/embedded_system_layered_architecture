#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "avr/interrupt.h"

#include "TIM1_interface.h"
#include "EXTI0_interface.h"
#include "EXTI0_register.h"

/* To Delete */
#include "LCD_interface.h"
#include "Log_interface.h"

volatile static u16 Temp_Read;
volatile static u16 Ton,Toff     ;

volatile static u8 flag =0;

void EXTI0_Initialize(void)
{
	/* ETI0 triggering source is rising edge */
	MCUCR_Register = 3;
	
	/* Enable INT 0*/
	SET_BIT(GICR_Register,6);
	
	/* Enable Global Interrupt */
	SET_BIT(SREG_Register,7);
}

void EXTI0_GetIcuSignal(u16* Freq, u16* Duty)
{
	if ((Ton+Toff) > 0)
	{
		*Duty = (Ton*100) / (Ton + Toff);
		*Freq = (u32)12000000/(Ton+Toff);
	}
	


}

ISR (INT0_vect)
{

	if (flag == 0)
	{
		TIM1_Reset();

		flag  = 1;
	}

	else if (flag == 1)
	{
		Temp_Read = TIM1_GetCounterValue();
		TIM1_Reset();
		
		/* Change mode to falling edge */
		MCUCR_Register = 2;
		flag = 2;


	}

	else if (flag == 2)
	{
		Toff = TIM1_GetCounterValue();
		Ton  = Temp_Read;
		TIM1_Reset();
		
		/* Change mode to rising edge */
		MCUCR_Register = 3;
		flag = 1;
	}
}
