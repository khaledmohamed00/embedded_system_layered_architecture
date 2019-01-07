#ifndef __BSP_H__
#define __BSP_H__
#include "TM4C123GH6PM.h"
#include "tm4c123gh6pm.h"
/* Board Support Package for the EK-TM4C123GXL board */

/* system clock setting [Hz] */
#define SYS_CLOCK_HZ 16000000U

/* on-board LEDs */

void ADC0_InitSWTriggerSeq3_Ch9(void);
unsigned long ADC0_InSeq3(void);

#endif // __BSP_H__
