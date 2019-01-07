/* Board Support Package */

#include "uart.h"
#include "TM4C123GH6PM.h"
#include <string.h>
#include <stdlib.h>
__attribute__((naked)) void assert_failed (char const *file, int line) {
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}

// Assumes a 16 MHz bus clock, creates 9600 baud rate
void UART_Init(void){            // should be called only once
    // 1. Enable the UART module using the RCGCUART register (see page 344).
       SYSCTL->RCGCUART |= (1<<1);

       // 2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 340).
       // To find out which GPIO port to enable, refer to Table 23-5 on page 1351.
       SYSCTL->RCGCGPIO |= (1<<2);

       // 3. Set the GPIO AFSEL bits for the appropriate pins (see page 671). To determine which GPIOs to
       // configure, see Table 23-4 on page 1344
       GPIOC->AFSEL = (1<<4)|(1<<5);

       // 4. Configure the GPIO current level and/or slew rate as specified for the mode selected (see
       // page 673 and page 681

       // 5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate
       // pins (see page 688 and Table 23-5 on page 1351).

       GPIOC->PCTL = (GPIOC->PCTL&0xFF00FFFF)+0x00220000;

       GPIOC->DEN = (1<<4)|(1<<5);

       // Find  the Baud-Rate Divisor
       // BRD = 16,000,000 / (16 * 9600) = 104.16666666666666666666666666666666666666666666666666
       // UARTFBRD[DIVFRAC] = integer(0.166667 * 64 + 0.5) = 11


       // With the BRD values in hand, the UART configuration is written to the module in the following order

       // 1. Disable the UART by clearing the UARTEN bit in the UARTCTL register
       UART1->CTL &= ~(1<<0);

       // 2. Write the integer portion of the BRD to the UARTIBRD register
       UART1->IBRD = 104;
       // 3. Write the fractional portion of the BRD to the UARTFBRD register.
       UART1->FBRD = 11;

       // 4. Write the desired serial parameters to the UARTLCRH register (in this case, a value of 0x0000.0060)
       UART1->LCRH = (0x3<<5)|(1<<4);     // 8-bit, no parity, 1-stop bit

       // 5. Configure the UART clock source by writing to the UARTCC register
       UART1->CC = 0x0;

       // 6. Optionally, configure the µDMA channel (see “Micro Direct Memory Access (µDMA)” on page 585)
       // and enable the DMA option(s) in the UARTDMACTL register

       // 7. Enable the UART by setting the UARTEN bit in the UARTCTL register.
       UART1->CTL = (1<<0)|(1<<8)|(1<<9);

}
char readChar(void)
{
    char c=0x00;
    while((UART1->FR & (1<<4)) != 0);
    c = UART1->DR;

    return c;
}

void printChar(char c)
{
    while((UART1->FR & (1<<5)) != 0);
    UART1->DR = c;
}

void printString(char * string)
{
  while(*string !='\0')
  {
    printChar(*(string++));
  }
}

char* readString(char delimiter)
{

  int stringSize = 0;
  char* string = (char*)malloc(10*sizeof(char));
  char c = readChar();
  printChar(c);

  while(c!=delimiter)
  {

    *(string+stringSize) = c; // put the new character at the end of the array
    stringSize++;

    if((stringSize%10) == 0) // string length has reached multiple of 10
    {
      string = (char*)realloc(string,(stringSize+10)*sizeof(char)); // adjust string size by increasing size by another 10
    }

    c = readChar();
    printChar(c); // display the character the user typed
  }

  if(stringSize == 0)
  {

    return '\0'; // null car
  }
  string[stringSize]='\0';
  return string;
}

