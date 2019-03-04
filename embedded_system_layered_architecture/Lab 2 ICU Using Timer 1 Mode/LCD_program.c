/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/
/* Description ! 16x2 Character LCD for chip LMB161A                                   */
/* Release Date! 28/6/2016                                                             */
/* Version     ! V01                                                                   */
/***************************************************************************************/

/********************************** Header Files INCLUSIONS ****************************/
#include "STD_TYPES.h"
#define F_CPU 12000000
#include "util/delay.h"

#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_Extra.h"
#include "LCD_Config.h"
/***************************************************************************************/



/***************************************************************************************/
/********************************** Fucntion Definition ********************************/
/***************************************************************************************/

/***************************************************************************************/
/********************************** Macros *********************************************/
/***************************************************************************************/

#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* return cursor to first position on first line                   */
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0x80          // set cursor position

/***************************************************************************************/
/********************************** Constant Variables *********************************/
/***************************************************************************************/



/***************************************************************************************/
/* Description! Apply initialization sequence for LCD module                           */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_voidInit(void)
{
	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(30);

	/* Return Home  */
	LCD_voidSendCommand(lcd_Home);
	_delay_ms(15);

	/* Function Set  */
	LCD_voidSendCommand(lcd_FunctionSet8bit);
	_delay_ms(1);

	/* Display ON OFF Control */
	LCD_voidSendCommand(lcd_DisplayOn);
	_delay_ms(1);

	/* Clear Display */
	LCD_voidSendCommand(lcd_Clear);
	_delay_ms(15);

	/* Entry Mode Set  */
	LCD_voidSendCommand(lcd_EntryMode);
	_delay_ms(2);

}


/***************************************************************************************/
/* Description! Interface to send the configuration commands to the LCD Driver         */
/* Input      ! Command number                                                         */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_voidSendCommand(u8 u8CmdCpy)
{

	/* Set RS to LOW */
	DIO_SetPinValue(LCD_CTRL_PORT, RS_PIN, LOW);

	/* Set R/W to LOW */
	DIO_SetPinValue(LCD_CTRL_PORT, RW_PIN, LOW);

	/* Set E to HIGH  */
	DIO_SetPinValue(LCD_CTRL_PORT, E_PIN, HIGH);

	/* Load Command on Data bus */
	DIO_SetPortValue(LCD_DATA_PORT, u8CmdCpy);

	/* Set E to LOW */
	DIO_SetPinValue(LCD_CTRL_PORT, E_PIN, LOW);

	/* Wait for E to settle */
	_delay_ms(1);

	/* Set E to HIGH */
	DIO_SetPinValue(LCD_CTRL_PORT, E_PIN, HIGH);

	/* Delay for 10ms to let the LCD execute command */
	_delay_ms(1);

}

/***************************************************************************************/
/* Description! Interface to write character on LCD screen                             */
/* Input      ! Data to send                                                           */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_voidWriteCharctr(u8 u8DataCpy)
{
	/* Set RS to HIG */
	DIO_SetPinValue(LCD_CTRL_PORT, RS_PIN, HIGH);

	/* Set R/W to LOW */
	DIO_SetPinValue(LCD_CTRL_PORT, RW_PIN, LOW);

	/* Set E to HIGH */
	DIO_SetPinValue(LCD_CTRL_PORT, E_PIN, HIGH);

	/* Load Command on Data bus */
	DIO_SetPortValue(LCD_DATA_PORT, u8DataCpy);

	/* Set E to LOW */
	DIO_SetPinValue(LCD_CTRL_PORT, E_PIN, LOW);

	/* Wait for E to settle */
	_delay_ms(1);

	/* Set E to HIGH */
	DIO_SetPinValue(LCD_CTRL_PORT, E_PIN, HIGH);

	/* Delay for 10ms to let the LCD execute command */
	_delay_ms(1);

}

/***************************************************************************************/
/* Description! Interface to start the writing process at certain digit in the LCD     */
/* Input      ! Y = Row position , X = Column position                                 */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_voidGotoxy (u8 Y,u8 X)
{
	if (X>0 && X<=16)
	{
	    switch(Y)
	    {
		    case 1: LCD_voidSendCommand(X+127); break;
		    case 2: LCD_voidSendCommand(X+191); break;
		    default:                           break;
	    }
	}
}

/***************************************************************************************/
/* Description! Interface to write extra characters saved in the CGRAM                 */
/* Input      ! Y = Row position , X = Column position                                 */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_voidWriteExtraChar (u8 Y,u8 X)
{
    u8 iteration1,iteration2;

    /*DDRAM-->CGRAM*/
    LCD_voidSendCommand(64);
	for(iteration1=0 ; iteration1<64 ; iteration1++)
	{
		LCD_voidWriteCharctr(ExtraChar[iteration1]);
	}
	/*CGRAM-->DDRAM*/
	LCD_voidSendCommand(128);
	LCD_voidGotoxy(Y,X);
	/*First eight character which saved at CGRAM*/
	for (iteration2=0; iteration2<=7 ; iteration2++)
	{
		/* Write bytes of DDRAM */
		LCD_voidWriteCharctr(iteration2);

		_delay_ms(5);
	}
}
