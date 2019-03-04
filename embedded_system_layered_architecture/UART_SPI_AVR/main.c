#define F_CPU 8000000ul
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>
#include "STD_TYPES.h"
#include "UART_int.h"
#include<avr/io.h>


/*void USART_SendString(char * string){
int index=0;
while(string[index] !='\0')
{uart_send_char(string[index]);
index++;
}
}
*/
char _number[20];
char _buffer[20];

int main(void){

uart_init();
spi_slave_init();
//DDRA=0xff;
//u8 recieved_data=0xff;




while(1){

//recieved_data=uart_receive_char();
//PORTC=recieved_data;
//uart_send_char(recieved_data);
//u8 data=SPI_SlaveReceive();	

dtostrf( (double)125, 5, 2, _number );					/* Take values in buffer to send all parameters over USART */
sprintf(_buffer," Ax = %s g\n",_number);
USART_SendString(_buffer);

//uart_send_char('1');	
//PORTA=0xff;
}

}

