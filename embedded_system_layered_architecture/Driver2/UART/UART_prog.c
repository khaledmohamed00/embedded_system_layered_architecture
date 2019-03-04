#define F_CPU 8000000UL
#include<avr/io.h>
#include "uart.h"



void uart_init(void){
DDRD|=(1<<DDD1);
DDRD&=~(1<<DDD0);
UBRRL = 0x33;//set baudrate 9600
UBRRH = 0;
UCSRC=(1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);  // Set Frame Format -> 8 data, 1 stop, No Parity
UCSRB=(1<<RXEN)|(1<<TXEN);// Enable RX and TX


}

void uart_send_char(unsigned char c){
while(!(UCSRA & (1<<UDRE)));

      UDR=c;

}

unsigned char uart_receive_char(void){
while(!(UCSRA & (1<<RXC)));
return UDR;
}
