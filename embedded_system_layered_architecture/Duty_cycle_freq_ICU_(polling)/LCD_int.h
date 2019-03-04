#ifndef LCD_INT_H
#define LCD_INT_H




void LCD_cmd(u8 cmd);
void init_LCD(void);
void LCD_write(u8 data);
void LCD_write_string(u8 *str);
void LCD_write_int(u16 number);
void LCD_write_double(f64 number);
void LCD_build_special_char(u8 location,u8 *ptr);
void LCD_goto(u8 x,u8 y);
void LCD_vidWriteU16 (u16 u16ValCpy);


#endif
