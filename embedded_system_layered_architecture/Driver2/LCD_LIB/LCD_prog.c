#define F_CPU 8000000UL

#include<util/delay.h>
#include <stdlib.h>
#include <math.h>  
#include "STD_TYPES.h"
#include "DIO_int.h"
#include "LCD_int.h"
#include "LCD_config.h"
void init_LCD(void)
{
DIO_u8SetPortDirection(LCD_DATA,0xff);
DIO_u8SetPortDirection(LCD_ctrl,0x07);

LCD_cmd(0x38);                            // initialization of 16X2 LCD in 8bit mode
_delay_ms(1);
LCD_cmd(0x01);                                 // clear LCD
_delay_ms(1);
LCD_cmd(0x0E);                        // cursor ON
_delay_ms(1);
LCD_cmd(0x80);                     // —8 go to first line and –0 is for 0th position
_delay_ms(1);
return;

}

void LCD_cmd(u8 cmd)
{


DIO_u8SetPortValue(LCD_DATA,cmd);
DIO_u8SetPortValue(LCD_ctrl,(0<<rs)|(0<<rw)|(1<<en));
_delay_ms(1);
DIO_u8SetPortValue(LCD_ctrl,(0<<rs)|(0<<rw)|(0<<en));

_delay_ms(50);
return;

}

void LCD_write(u8 data)
{

DIO_u8SetPortValue(LCD_DATA,data);
DIO_u8SetPortValue(LCD_ctrl,(1<<rs)|(0<<rw)|(1<<en));
_delay_ms(1);

DIO_u8SetPortValue(LCD_ctrl, (1<<rs)|(0<<rw)|(0<<en));
_delay_ms(50);
return ;

}

void LCD_write_string(u8 *str)             //store address value of the string in pointer *str
{
int i=0;
while(str[i]!='\0')                               // loop will go on till the NULL character in the string
{
LCD_write(str[i]);                            // sending data on LCD byte by byte
i++;
}
return;
}

void LCD_write_int(s16 number){

s16 num=number;
s16 digits=0;
s16 index;
while(num>0){
digits++;
num/=10;
}
index=digits-1;
u8 * arr=malloc((digits+1)* sizeof(u8));
while(index>=0){
s16 rem=number%10;
number=number/10;
arr[index--]=rem+'0';
}
arr[digits]='\0';
LCD_write_string(arr);

}

void LCD_write_double(f64 number){

s16 num=(s16)number;

LCD_write_int(num);
LCD_write('.');
s16 factor=(s16)(fmod( number, 1.0 )*100);
LCD_write_int(factor);

}

void LCD_build_special_char(u8 location,u8 *ptr){

if(location<8){

LCD_cmd(0x40+location*8);
u8 i=0;
for(i=0;i<8;i++){
LCD_write(ptr[i]);

}

}

}

void LCD_goto(u8 x,u8 y){

if(x<16){

if(y==0){
LCD_cmd(0x80+x);
}else if(y==1){
LCD_cmd(0xBF+x);
}else{}
}

}

