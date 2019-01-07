#ifndef __UART_H__
#define __UART_H__
#include "TM4C123GH6PM.h"
#include "tm4c123gh6pm.h"


void UART_Init(void);
unsigned char UART_InChar(void);
void UART_OutChar(unsigned char data);
unsigned char UART_InCharNonBlocking(void);
#endif // __UART_H__
