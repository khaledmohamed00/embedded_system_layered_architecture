#define F_CPU 8000000UL
#include"STD_TYPES.h"
#include<avr/io.h>
#include "UART_int.h"



void uart_init(void){
DDRD|=(1<<DDD1);
DDRD&=~(1<<DDD0);
UBRRL = 0x33;//set baudrate 9600
UBRRH = 0;
UCSRC=(1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);  // Set Frame Format -> 8 data, 1 stop, No Parity
UCSRB=(1<<RXEN)|(1<<TXEN);// Enable RX and TX


}

void uart_send_char(u8 c){
while(!(UCSRA & (1<<UDRE)));

      UDR=c;

}

u8 uart_receive_char(void){
while(!(UCSRA & (1<<RXC)));
return UDR;
}

