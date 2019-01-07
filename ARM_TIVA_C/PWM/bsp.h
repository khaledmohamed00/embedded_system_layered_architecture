#ifndef __UART_H__
#define __UART_H__
#include "TM4C123GH6PM.h"
#include "tm4c123gh6pm.h"
/* Board Support Package for the EK-TM4C123GXL board */

/* system clock setting [Hz] */
#define SYS_CLOCK_HZ 80000000U

/* on-board LEDs */
#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)
//void PortF_Init(void);
void PLL_Init(void);
void SysTick_Handler(void);
void GPIOPortF_IRQHandler(void);
void Switch_Init(void);
void Motor_Init(void);
#endif // __BSP_H__
