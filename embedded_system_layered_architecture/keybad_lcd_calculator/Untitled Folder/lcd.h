#ifndef LCD_H
#define LCD_H

#define LCD_DDR 0
#define LCD_DATA 0               //LCD data port
#define ctrl 1
#define ctrl_DDR 1
#define en 2                         // enable signal
#define rw 1                       // read/write signal
#define rs 0                     // register select signal
void LCD_cmd(u8 cmd);
void init_LCD(void);
void LCD_write(u8 data);
void LCD_write_string(u8 *str);
void LCD_write_int(s16 number);
void LCD_write_double(f64 number);





#endif
