#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIM0_register.h"
#include "TIM0_Interface.h"

void TIM0_initialize(void)
{
	/* Fast PWM - Clock DIV by 1 */
	TCCR0_Register = 0b01111011;
	
	/* Set OCR to 128 to have duty cycle 50 % */
	OCR0_Register = 64;
	
}
