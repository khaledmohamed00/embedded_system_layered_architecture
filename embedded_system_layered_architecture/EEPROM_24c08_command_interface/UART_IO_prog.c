#include"STD_TYPES.h"
#include "UART_int.h"




u32 power(u16 base,u16 power){
u32 num=1;
if(power==0u)
return 1;
else{
u16 i;	
for(i=1;i<=power;i++){
num=num*base;
}

return num;
}

}


void int_to_array_of_char(u16 number,u8 * array_of_char){

u16 digits=0;
u16 temp=number;
while(temp!=0){
digits++;
temp=temp/10;
}
temp=digits;
while(number!=0 ){
u16 digit=number%10;
number=number/10;
array_of_char[temp-1]=digit+'0';
temp--;
}
array_of_char[digits]='\0';

}



u32 u32_array_of_char_to_int(u8 * array){

u8 index=0;
u32 number=0;
u8 digits=0;
while(array[digits]!='\0'){
digits++;
}
digits--;
while(array[index]!='\0'){


number=number+((array[index]-'0')*(u32)power(10,digits));
index++;
digits--;
}

return number;

}


void USART_SendString(char * string){

int index=0;
while(string[index] !='\0')
{uart_send_char(string[index]);
index++;
}

}



void read_string_uart(u8 * recived_data_buffer )
{
     u8 data=uart_receive_char();
     uart_send_char(data);
     u16 index=0;
     while(data !=13){
     recived_data_buffer[index++]=data;
     data=uart_receive_char();
     uart_send_char(data);

     }
     recived_data_buffer[index]='\0';
     USART_SendString("\r\n");

}





void printf_int_uart(u32 number,u8* recived_data_buffer)
{

int_to_array_of_char(number,recived_data_buffer);
USART_SendString(recived_data_buffer);

}



void scanf_int_uart(u32 *number,u8* recived_data_buffer)
{
  read_string_uart( recived_data_buffer );
  *number=u32_array_of_char_to_int(recived_data_buffer);

}



