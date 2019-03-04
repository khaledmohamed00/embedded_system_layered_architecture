
#include"STD_TYPES.h"
#include "UART_int.h"
#include "UART_IO_int.h"


int main ()
{ u8 array_of_char[12];
  u8 recived_data_buffer[12];
 uart_init();
 
 u32 num;
 
  while(1){
  	 scanf_int_uart(&num,recived_data_buffer);

     printf_int_uart(num,recived_data_buffer);
      
     USART_SendString("\r\n");
     

	}


}
