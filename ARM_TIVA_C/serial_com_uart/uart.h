#ifndef __UART_H__
#define __UART_H__

char readChar(void);
void printChar(char c);
void printString(char * string);
char* readString(char delimiter);
void UART_Init(void);

#endif // __UART_H__
