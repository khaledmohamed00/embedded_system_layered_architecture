#ifndef _UART_IO_INT_H
#define _UART_IO_INT_H

u32 power(u16 base,u16 power);
void int_to_array_of_char(u16 number,u8 * array_of_char);
u32 u32_array_of_char_to_int(u8 * array);
void USART_SendString(char * string);
void read_string_uart(u8 * recived_data_buffer );
void printf_int_uart(u32 number,u8* recived_data_buffer);
void scanf_int_uart(u32 *number,u8* recived_data_buffer);

#endif