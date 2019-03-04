/********************************************************/
/* Author    : Ahmed Assaf                              */
/* Date      : 23/3/2018                                */
/* Version   : V01                                      */
/********************************************************/
#ifndef _TIM0_INT_H
#define _TIM0_INT_H

void TIM0_voidInitialize(void);

void TIM0_voidSetTimerReg(u8 Copy_u8Value);

void TIM0_voidSetCompareVal(u8 Copy_u8Value);

void TIM0_voidEnableOVINT(void);

void TIM0_voidDisableOVINT(void);

void TIM0_voidEnableCTCINT(void);

void TIM0_voidDisableCTCINT(void);

void TIM0_voidSetOVCallback( void (*Copy_ptr) (void) );

void TIM0_voidSetCTCCallback( void (*Copy_ptr) (void) );

#endif






