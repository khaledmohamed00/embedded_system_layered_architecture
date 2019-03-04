/*
 * LCD_Driver.c
 *
 *  Created on: Aug 11, 2017
 *      Author: Mohamed Waleed
 */
//#include "avr/io.h"

#define F_CPU 12000000UL
#include <avr/delay.h>

#include "utilss.h"
#include "STD_Types.h"
#include "DIO.h"
#include "LCD.h"
#include "FreeRTOS.h"

extern void LCD_voidInit(void)
{

	//RS pin
	DIO_voidSetPinDirection(LCD_RS,DIO_u8PinOp);
	//RW pin
	DIO_voidSetPinDirection(LCD_RW,DIO_u8PinOp);
	//En pin
	DIO_voidSetPinDirection(LCD_E,DIO_u8PinOp);

	/*
	DIO_voidSetPinDirection(LCD_D0,DIO_u8PinOp);
	DIO_voidSetPinDirection(LCD_D1,DIO_u8PinOp);
	DIO_voidSetPinDirection(LCD_D2,DIO_u8PinOp);
	DIO_voidSetPinDirection(LCD_D3,DIO_u8PinOp);
	DIO_voidSetPinDirection(LCD_D4,DIO_u8PinOp);
	DIO_voidSetPinDirection(LCD_D5,DIO_u8PinOp);
	DIO_voidSetPinDirection(LCD_D6,DIO_u8PinOp);
	DIO_voidSetPinDirection(LCD_D7,DIO_u8PinOp);
*/
	DIO_voidSetPortDirection(LCD_Data_Port,255);

//	DIO_voidSetPortDirection(LCD_Data_Port,255);

	//1) wait for 4.5 ms => delay 50 ms
	_delay_ms(50);
	//write command 0b00111000; 	DB3(0:one line && 1:two lines)
	LCD_voidWriteCommand(0b00111000);
	//DElay 1ms
	_delay_ms(1);
	//write command 0b00001100
	LCD_voidWriteCommand(0b00001110);
	//delay 1ms
	_delay_ms(1);
	//write command 0b00000001
	LCD_voidWriteCommand(0b00000001);
	//delay 2ms
	_delay_ms(2);
}
/**********************************************************************
 *
 *
 **********************************************************************
 */
extern void LCD_voidWriteCommand(u8 Command)
{
	// RS=0
	DIO_voidWritePinValue(LCD_RS,DIO_u8LOW);

	//RW=0
	DIO_voidWritePinValue(LCD_RW,DIO_u8LOW);

	//DataBus = command
	DIO_voidWritePortValue(LCD_Data_Port,Command);

	//E=1
	DIO_voidWritePinValue(LCD_E,DIO_u8HIGH);

	//Delay 2ms
	_delay_ms(2);

	//E=0
	DIO_voidWritePinValue(LCD_E,DIO_u8LOW);
}
/**********************************************************************
 *
 *
 **********************************************************************
 */
extern void LCD_voidDisplayData(u8 Data)
{
	// RS=1
	DIO_voidWritePinValue(LCD_RS,DIO_u8HIGH);

	//RW=0
	DIO_voidWritePinValue(LCD_RW,DIO_u8LOW);

	//DataBus = Data
	DIO_voidWritePortValue(LCD_Data_Port,Data);

	//E=1
	DIO_voidWritePinValue(LCD_E,DIO_u8HIGH);

	vTaskDelay(2);

//	//Delay 2ms
//	_delay_ms(2);

	//E=0
	DIO_voidWritePinValue(LCD_E,DIO_u8LOW);
}
/**********************************************************************
 *
 *
 **********************************************************************
 */
extern void LCD_voidGoToPos(u8 Copy_u8RowNum,u8 Copy_u8ColNum)
{

	LCD_voidWriteCommand(0b10000000);
	if(Copy_u8RowNum==1)
	{
		if (Copy_u8ColNum>0 && Copy_u8ColNum <=16)
		{
			LCD_voidWriteCommand(127+Copy_u8ColNum);
		}
	}
	else if (Copy_u8RowNum==2)
	{
		if (Copy_u8ColNum>0 && Copy_u8ColNum <=16)
		{
			LCD_voidWriteCommand(191+Copy_u8ColNum);
		}
	}

}


//========================================================================================
extern void LCD_voidWriteChar(u8 Copy_u8RowNum,u8 Copy_u8ColNum,u8 Copy_u8Char)
{
	LCD_voidGoToPos(Copy_u8RowNum,Copy_u8ColNum);
	LCD_voidDisplayData(Copy_u8Char);
}
//=========================================================================================
extern void LCD_voidWriteCharr(u8 Copy_u8Char)
{
	LCD_voidDisplayData(Copy_u8Char);
}
//=========================================================================================
extern void LCD_voidWriteSentence(u8 Copy_u8RowNum,u8 Copy_u8ColNum,u8 *Copy_u8CharArr)
{
	u8 Local_u8Counter;
	LCD_voidGoToPos(Copy_u8RowNum,Copy_u8ColNum);
	for (Local_u8Counter=0;Copy_u8CharArr[Local_u8Counter]!='\0';Local_u8Counter++)
	{
		LCD_voidDisplayData(Copy_u8CharArr[Local_u8Counter]);

	}

}
//=======================================================================================

extern void LCD_voidWriteSentencee(u8 *Copy_u8CharArr)
{
	u8 Local_u8Counter;
	for(Local_u8Counter=0;Copy_u8CharArr[Local_u8Counter]!='\0';Local_u8Counter++)
	{
		LCD_voidDisplayData(Copy_u8CharArr[Local_u8Counter]);

	}

}
//=======================================================================================
extern void LCD_DispalyNumber(u32 x)
{
	u32 y = 1;
	if (x == 0)
	{
		LCD_voidDisplayData('0');
	}
	if (x < 0) {
		LCD_voidDisplayData('-');
		x *= -1;
	}
	while (x != 0) {
		y = ((y * 10) + (x % 10));
		x = (x / 10);
	}
	while (y != 1) {
		LCD_voidDisplayData((y % 10) + 48);
		y = (y / 10);
	}
}
