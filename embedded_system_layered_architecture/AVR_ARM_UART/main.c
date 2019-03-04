#define F_CPU 8000000ul

#include "STD_TYPES.h"
#include "UART_int.h"
#include<avr/io.h>
int main(void){

uart_init();
//spi_slave_init();
//DDRA=0xff;
//u8 recieved_data=0xff;
while(1){

//recieved_data=uart_receive_char();
//PORTC=recieved_data;
//uart_send_char(recieved_data);
//u8 data=SPI_SlaveReceive();
uart_send_char('1');	
PORTA=0xff;
}

}

