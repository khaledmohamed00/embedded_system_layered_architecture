#ifndef EEPROM_H
#define EEPROM_H

void EEPROM_Init(void);
u8 EEPROM_WriteByte(u16 addr, u8 data,u8 stop);
u8 EEPROM_ReadByte(u16 addr, u8 *data,u8 stop);

#endif
