#include"STD_TYPES.h"
#include"eeprom.h"
#include"IIC.h"
#include "UART_int.h"
#include "UART_IO_int.h"
#define stop 1
#define no_stop 0
int main ()
{ u8 array_of_char[12];
  u8 recived_data_buffer[12];
 uart_init();
 EEPROM_Init();
 
 u32 data32;
 u8 data8;
 
 u32 no_of_bytes;
 u32 address;
 u8 flag_w;
 u8 flag_r;
 USART_SendString("EEPROM 24c08 interface");

 USART_SendString("\r\n");
 USART_SendString(" *************************************************************************************");
 USART_SendString("\r\n");

  while(1){
  	USART_SendString(" *******************************************************************************************************");
    USART_SendString("\r\n");
  	USART_SendString("EEPROM 24c08 interface options : for read press r for write press w  :   ");
  	USART_SendString("\r\n");
  	USART_SendString(" for read press r  :   ");
    USART_SendString("\r\n");
  	USART_SendString(" for write press w  :   ");
    USART_SendString("\r\n");
    USART_SendString(" for multiple read press mr  :   ");
    USART_SendString("\r\n");
    USART_SendString(" for multiple write press mw  :   ");
    USART_SendString("\r\n");
    USART_SendString("the command :  ");


  	read_string_uart(array_of_char);
    USART_SendString("\r\n");
    if(array_of_char[0]=='w')
    {

      USART_SendString("enter the address you want to write in from 0 to 1023 : ");
  	  scanf_int_uart(&address,recived_data_buffer);
  	  USART_SendString("\r\n");
      USART_SendString("enter the data format decimal or ascii  d or a: ");
      read_string_uart(array_of_char);
      USART_SendString("\r\n");

      if(array_of_char[0]=='d')     
      {USART_SendString("enter the data in decimal format from 0 to 255 : "); 

       scanf_int_uart(&data32,recived_data_buffer);
       USART_SendString("\r\n");
       flag_w=EEPROM_WriteByte(address,(u8)data32,stop);
       }
       else if(array_of_char[0]=='a')
      {USART_SendString("enter the data in ascii format : ");
       read_string_uart(array_of_char);
       flag_w=EEPROM_WriteByte(address,(u8)array_of_char[0],stop);


    }
    }	
    else if(array_of_char[0]=='r')
    { USART_SendString("enter the address you want to read from 0 to 1023 : ");
      scanf_int_uart(&address,recived_data_buffer);
  	  USART_SendString("\r\n");
      USART_SendString("enter the data format decimal or ascii  d or a: ");
      read_string_uart(array_of_char);
  	  USART_SendString("\r\n");

      if(array_of_char[0]=='d') 
      {
      	flag_r=EEPROM_ReadByte(address,&data8,stop);
        data32=(u32)data8;
        USART_SendString("the data :");
        printf_int_uart(data32,recived_data_buffer);
        USART_SendString("\r\n");

      }
      else if(array_of_char[0]=='a')
      { 

       flag_r=EEPROM_ReadByte(address,&data8,stop);
        //data32=(u32)data8;
        //printf_int_uart(data32,recived_data_buffer);
       USART_SendString("the data :");
       uart_send_char(data8); 
       USART_SendString("\r\n");

      }
      
    }

//multiple read
      else if(array_of_char[0]=='m' && array_of_char[1]=='r'){
      USART_SendString("enter the start address you want to read from 0 to 1023 : ");
  	  scanf_int_uart(&address,recived_data_buffer);
  	  USART_SendString("\r\n");
      
      USART_SendString("enter the number of bytes : ");
  	  scanf_int_uart(&no_of_bytes,recived_data_buffer);
  	  USART_SendString("\r\n");

  	  USART_SendString("enter the data format decimal or ascii  d or a: ");
      read_string_uart(array_of_char);
      USART_SendString("\r\n");

      if(array_of_char[0]=='d') 
      {

      

      flag_r=EEPROM_ReadByte(address,&data8,no_stop);
      data32=(u32)data8;
      USART_SendString("the data :");
      printf_int_uart(data32,recived_data_buffer);
      USART_SendString("\r\n");
     int i;
     for(i=0;i<no_of_bytes-1;i++){
        
        data8=TWIReadACK();
        data32=(u32)data8;
        USART_SendString("the data :");
        printf_int_uart(data32,recived_data_buffer);
        USART_SendString("\r\n");
     }
     }
     else if(array_of_char[0]=='a') 
      {flag_r=EEPROM_ReadByte(address,&data8,no_stop);
      data32=(u32)data8;
      USART_SendString("the data :");
      uart_send_char(data8); 
      USART_SendString("\r\n");
     int i;
     for(i=0;i<no_of_bytes-1;i++){
        
        data8=TWIReadACK();
        data32=(u32)data8;
        USART_SendString("the data :");
       uart_send_char(data8); 
       USART_SendString("\r\n");
         
      }

     TWIStop();
    }
	
	}
  else if(array_of_char[0]=='m' && array_of_char[1]=='w'){
     
USART_SendString("enter the start address you want to write in from 0 to 1023 : ");
      scanf_int_uart(&address,recived_data_buffer);
      USART_SendString("\r\n");
      
      USART_SendString("enter the number of bytes : ");
      scanf_int_uart(&no_of_bytes,recived_data_buffer);
      USART_SendString("\r\n");

      USART_SendString("enter the data format decimal or ascii  d or a: ");
      read_string_uart(array_of_char);
      USART_SendString("\r\n");

      if(array_of_char[0]=='d') 
      {
      //USART_SendString("enter the address you want to write in from 0 to 1023 : ");
      //scanf_int_uart(&address,recived_data_buffer);
      //USART_SendString("\r\n");
      USART_SendString("enter the data in decimal format from 0 to 255 : "); 
      scanf_int_uart(&data32,recived_data_buffer);
      USART_SendString("\r\n");
      flag_w=EEPROM_WriteByte(address,(u8)data32,no_stop);
      int j;
      for(j=0;j<no_of_bytes-1;j++){
       USART_SendString("enter the data in decimal format from 0 to 255 : "); 
       scanf_int_uart(&data32,recived_data_buffer);
       USART_SendString("\r\n");
       //flag_w=EEPROM_WriteByte_no_stop(address,(u8)data32,no_stop);
       data8=(u8)data32;
       TWIWrite(data8);
      }
      }
      else if(array_of_char[0]=='a') 
      {USART_SendString("enter the data in ascii format : ");
       read_string_uart(array_of_char);
       flag_w=EEPROM_WriteByte(address,(u8)array_of_char[0],no_stop);
       int j;
      for(j=0;j<no_of_bytes-1;j++){
      USART_SendString("enter the data in ascii format  : "); 
      read_string_uart(array_of_char);
      USART_SendString("\r\n");
      data8=(u8)array_of_char[0];
      TWIWrite(data8);
      }




      }


     
      
      TWIStop();
    }
   

}
}

    
/*****************************************************************************************/
     //multiple write
      /*else if(array_of_char[0]=='m' && array_of_char[1]=='r'){
      USART_SendString("enter the address you want to write in from 0 to 1023 : ");
  	  scanf_int_uart(&address,recived_data_buffer);
  	  USART_SendString("\r\n");
  	  USART_SendString("enter the data in decimal format from 0 to 255 : "); 
      scanf_int_uart(&data32,recived_data_buffer);
      USART_SendString("\r\n");
      flag_w=EEPROM_WriteByte(address,(u8)data32,no_stop);
      int j;
      for(j=0;j<3;j++){
       USART_SendString("enter the data in decimal format from 0 to 255 : "); 
       scanf_int_uart(&data32,recived_data_buffer);
       USART_SendString("\r\n");
       //flag_w=EEPROM_WriteByte_no_stop(address,(u8)data32,no_stop);
       TWIWrite(data8);
      }
      
      TWIStop();}*/
/*************************************************************************************************/