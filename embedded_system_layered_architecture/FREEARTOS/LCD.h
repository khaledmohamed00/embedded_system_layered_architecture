/*
 * LCD.h
 *
 *  Created on: Aug 12, 2017
 *      Author: Mohamed Waleed
 */

#ifndef LCD_H_
#define LCD_H_

#define LCD_Control_Port PORTA_ID
#define LCD_RS DIO_u8PinA0
#define LCD_RW DIO_u8PinA1
#define LCD_E DIO_u8PinA2


#define LCD_Data_Port PORTC_ID
#define LCD_D0 DIO_u8PinC0
#define LCD_D1 DIO_u8PinC1
#define LCD_D2 DIO_u8PinC2
#define LCD_D3 DIO_u8PinC3
#define LCD_D4 DIO_u8PinC4
#define LCD_D5 DIO_u8PinC5
#define LCD_D6 DIO_u8PinC6
#define LCD_D7 DIO_u8PinC7


#define LCD_Clear_Screen 0b00000001



extern void LCD_voidInit(void);
extern void LCD_voidWriteCommand(u8 Command);
extern void LCD_voidDisplayData(u8 Data);
extern void LCD_voidGoToPos(u8 Copy_u8RowNum,u8 Copy_u8ColNum);
extern void LCD_voidWriteChar(u8 Copy_u8RowNum,u8 Copy_u8ColNum,u8 Copy_u8Char);
extern void LCD_voidWriteCharr(u8 Copy_u8Char);
extern void LCD_voidWriteSentence(u8 Copy_u8RowNum,u8 Copy_u8ColNum,u8 *Copy_u8CharArr);
extern void LCD_voidWriteSentencee(u8 *Copy_u8CharArr);
extern void LCD_DispalyNumber(u32 x);

#endif /* LCD_H_ */
