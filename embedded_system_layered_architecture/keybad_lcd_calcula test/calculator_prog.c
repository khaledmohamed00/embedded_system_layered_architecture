#define F_CPU 8000000UL
//#include<avr/io.h>
#include<util/delay.h>
#include <stdlib.h>
#include <math.h>
#include "STD_TYPES.h"
#include "calculator_int.h"
#include "DIO_int.h"
#include "KPD_interface.h"
#include "lcd_int.h"
#define no_digits 10

/* this fuction transfers array of char to integer
   input:array of u8
   output:s16

*/
s16 arr_char_to_int(u8 * arr){
s16 index=0;

s16 rank;
while(arr[index]!='\0')
{index++;
}

rank=index;
index=0;
s16 number;
s16 sum=0;
while(arr[index]!='\0')
{number=arr[index]-'0';
sum+=number*(pow(10,rank-1));
index++;
rank--;
}
return sum;
}

/*this function makes mathematical operation on two numbers
  input:two array of u8 (argument),operation u8
  output: the result f64

 */

f64 calculate(u8 * first_arg,u8 * sec_arg,u8 op){
s16 first=arr_char_to_int(first_arg);
s16 second=arr_char_to_int(sec_arg);
switch(op){
case '+':
  return first+second;
case '-':
  return first-second;
case 'x':
  return (1.00*first)*(1.00*second);
case '/':
  return (1.00*first)/(1.00*second);

}
return -5;
}


/*the function that runs the calculator 
  input:void
  output:void
*/
u8 pattern[8]={0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};
void calculator(){

init_LCD();
LCD_build_special_char(0,pattern);
LCD_cmd(0x80);
LCD_write(0);
LCD_goto(5,1);
while(1){

}


/*_delay_ms(50);

u8 * first_arg=malloc(no_digits*sizeof(u8));   
u8 * sec_arg=malloc(no_digits*sizeof(u8));   
s16 index_first=0;
s16 index_sec=0;
s16 flag=0;
u8 op;
f64 result;
//DDRD=0x0f;
//PORTD=0xff;
DIO_SetPortDirection(PORTD,0x0f);
DIO_SetPortValue(PORTD,0xff);
while(1){


u8 key=KPD_u8GetPressedKey();

if((key !='+') &&(key!='-')&&(key !='x') &&(key!='=')&&(key !='/') && (key!='c')){
  if(flag==0){
    first_arg[index_first++]=key;
    first_arg[index_first]='\0';
             }
  else{
   sec_arg[index_sec++]=key;
   sec_arg[index_sec]='\0';
      }
         }
else if((key=='+')||(key=='*')||(key=='-')||(key=='x')||(key=='/')){
op=key;
flag=1;
}
else if(key=='=') {
result=calculate(first_arg,sec_arg,op);

LCD_write(key);
LCD_cmd(0x14);
flag=0;

if(result<0){
LCD_write('-');
LCD_cmd(0x14);
result*=-1;
}
//result*=-1;
//LCD_write_int(result);
LCD_write_double(result);
_delay_ms(2000);
}
else if(key=='c') {
LCD_cmd(0x01);
index_first=0;
index_sec=0;
}
if(key!='c' && key!='='){
LCD_write(key);
LCD_cmd(0x14);
LCD_cmd(0x10);
_delay_ms(2000);
}
}*/





}
