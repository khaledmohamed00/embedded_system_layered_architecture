/********************************************************/
/* Author    : Ahmed Assaf                              */
/* Date      : 23/3/2018                                */
/* Version   : V01                                      */
/********************************************************/
#ifndef _TIM0_CONFIG_H
#define _TIM0_CONFIG_H


/* Range: TIM0_u8_NORMAL           */
/*        TIM0_u8_CTC              */
/*        TIM0_u8_FAST_PWM         */
/*        TIM0_u8_PHASE_CORRECT    */
#define TIM0_u8_MODE    TIM0_u8_FAST_PWM

/* Range : TIM0_u8_DIV_BY_1        */
/*         TIM0_u8_DIV_BY_8        */
/*         TIM0_u8_DIV_BY_64       */
/*         TIM0_u8_DIV_BY_256      */
/*         TIM0_u8_DIV_BY_1024     */
#define TIM0_u8_PRE_SCALLER   TIM0_u8_DIV_BY_1


/* Range: TIM0_u8_NO_ACTION  */
/*        TIM0_u8_TOGGLE     */
/*        TIM0_u8_SET        */
/*        TIM0_u8_CLR        */
#define TIM0_COM_EVENT        TIM0_u8_CLR


#endif
