#include "uart.h"
#include "TM4C123GH6PM.h"



char cc;
int main(void)
{

    UART_Init();
    // Configure LED pins
    SYSCTL->RCGCGPIO |= (1<<5); // enable clock on PortF
    GPIOF->DIR = (1<<1)|(1<<2)|(1<<3);  // make LED pins (PF1, PF2, and PF3) outputs
    GPIOF->DEN = (1<<1)|(1<<2)|(1<<3); // enable digital function on LED pins
    GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3)); // turn off leds

    while(1)
    {

        for(char i=0;i<8;i++)
        {printChar((1<<i));
        cc=readChar();
        for(int j=0;j<1000000;j++){}
        }
        //GPIOF->DATA = cc;
        /*printString("Type something and press enter: ");
        char* string = readString('\r');
        printString("\n\r");
        printString("You typed: ");
        printString(string);
        printString("\n\r");
        free(string);*/
        /*char c=readChar();
        printString("\n\r");
        printChar(c);
        if(c=='r')
        {GPIOF->DATA = ((1<<1)|(0<<2)|(0<<3));
        }
        else if(c=='b')
        {
            GPIOF->DATA = ((0<<1)|(1<<2)|(0<<3));
        }
        else if(c=='g')
                {
                    GPIOF->DATA = ((0<<1)|(0<<2)|(1<<3));
                }*/
    }
}

