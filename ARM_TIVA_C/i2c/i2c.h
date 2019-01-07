#ifndef __I2C_H__
#define __I2C_H__
#include "TM4C123GH6PM.h"
#include "tm4c123gh6pm.h"


void setSlaveAddress(uint8_t slaveAddress);
void setRW(uint8_t mode);
void writeByte(uint8_t dataByte, uint8_t conditions);
void i2c_init(void);
#endif // __I2C_H__
