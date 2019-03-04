#ifndef LCD_H
#define LCD_H




#define LCD_DDR PORTA
#define LCD_DATA PORTA               //LCD data port
#define ctrl PORTB
#define ctrl_DDR PORTB
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
