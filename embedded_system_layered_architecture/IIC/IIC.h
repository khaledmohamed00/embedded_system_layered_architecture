#ifndef I2C_H
#define I2C_H

void I2C_Init(void);
void TWIStart(void);
void TWIStop(void);
void TWIWrite(unsigned char data);
unsigned char TWIReadACK(void);
unsigned char TWIReadNACK(void);
unsigned char TWIGetStatus(void);

#endif
