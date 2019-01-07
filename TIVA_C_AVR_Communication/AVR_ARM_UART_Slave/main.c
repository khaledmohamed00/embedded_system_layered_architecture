#define F_CPU 8000000ul

#include "STD_TYPES.h"
#include "UART_int.h"
#include<avr/io.h>
int main(void){

uart_init();
DDRC=0xff;
u8 recieved_data=0xff;
while(1){

recieved_data=uart_receive_char();
PORTC=recieved_data;
uart_send_char(recieved_data);
}

}

