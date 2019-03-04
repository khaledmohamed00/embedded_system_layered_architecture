/********************************************************/
/* Author    : Ahmed Assaf                              */
/* Date      : 23/3/2018                                */
/* Version   : V01                                      */
/********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIM0_reg.h"
#include "TIM0_priv.h"
#include "TIM0_config.h"
#include "TIM0_int.h"

void (*TIM0_OvCallback)(void);
void (*TIM0_CtcCallback)(void);

void TIM0_voidInitialize(void)
{
	#if   TIM0_u8_MODE == TIM0_u8_NORMAL
		CLR_BIT(TCCR0,6);
		CLR_BIT(TCCR0,3);
	
	#elif TIM0_u8_MODE == TIM0_u8_CTC
		CLR_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);
	
	#elif TIM0_u8_MODE == TIM0_u8_FAST_PWM
		SET_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);
	
	#elif TIM0_u8_MODE == TIM0_u8_PHASE_CORRECT
		SET_BIT(TCCR0,6);
		CLR_BIT(TCCR0,3);
	#endif
	
	#if TIM0_u8_PRE_SCALLER   == TIM0_u8_DIV_BY_1
		SET_BIT(TCCR0,0);	
	    CLR_BIT(TCCR0,1);
	    CLR_BIT(TCCR0,2);
	#elif TIM0_u8_PRE_SCALLER == TIM0_u8_DIV_BY_8
		CLR_BIT(TCCR0,0);	
	    SET_BIT(TCCR0,1);
	    CLR_BIT(TCCR0,2);
	#elif TIM0_u8_PRE_SCALLER == TIM0_u8_DIV_BY_64
		SET_BIT(TCCR0,0);	
	    SET_BIT(TCCR0,1);
	    CLR_BIT(TCCR0,2);
    #elif TIM0_u8_PRE_SCALLER == TIM0_u8_DIV_BY_256
		CLR_BIT(TCCR0,0);	
	    CLR_BIT(TCCR0,1);
	    SET_BIT(TCCR0,2);
	#elif TIM0_u8_PRE_SCALLER == TIM0_u8_DIV_BY_1024
		SET_BIT(TCCR0,0);	
	    CLR_BIT(TCCR0,1);
	    SET_BIT(TCCR0,2);
	#endif	
	
	//////////////////////////////////////////////////
    /* Set bits */
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);

	/* Disable the two interrupts */
	CLR_BIT(TIMSK,0);
	CLR_BIT(TIMSK,1);
	
	/* Clear Flags */
	SET_BIT(TIFR,0);
	SET_BIT(TIFR,1);
	
	/* Clear Registers  */
	TCNT0 = 0;
	OCR0  = 0;
	
}

void TIM0_voidSetTimerReg(u8 Copy_u8Value)
{
	TCNT0 = Copy_u8Value;
}

void TIM0_voidSetCompareVal(u8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}

void TIM0_voidEnableOVINT(void)
{
	SET_BIT(TIMSK,0);
}

void TIM0_voidDisableOVINT(void)
{
	CLR_BIT(TIMSK,0);
}

void TIM0_voidEnableCTCINT(void)
{
	SET_BIT(TIMSK,1);
}

void TIM0_voidDisableCTCINT(void)
{
	CLR_BIT(TIMSK,1);
}

void TIM0_voidSetOVCallback( void (*Copy_ptr) (void) )
{
	TIM0_OvCallback = Copy_ptr;
}

void TIM0_voidSetCTCCallback( void (*Copy_ptr) (void) )
{
	TIM0_CtcCallback = Copy_ptr;
}

void __vector_11 (void) __attribute__((signal,used));
void __vector_11 (void)
{
	TIM0_OvCallback();
}

void __vector_10 (void) __attribute__((signal,used));
void __vector_10 (void)
{
	TIM0_CtcCallback();
}










