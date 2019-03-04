#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "TIM1_register.h"
#include "TIM1_Interface.h"



void TIM1_initialize(void)
{
	/* Normal Mode , Prescaller DIV by 1 */
	TCCR1A_Register = 0;
	TCCR1B_Register = 1;

	
}

u16 TIM1_GetCounterValue(void)
{
	u8 Temp1 , Temp2;
	u16 Result;


	Temp1  = TCNT1L_Register;
	Temp2  = TCNT1H_Register;
	Result = Temp1 |( Temp2 << 8);
	
	return Result;
}

void TIM1_Reset(void)
{
	TCNT1L_Register = 0;
	TCNT1H_Register = 0;
}

