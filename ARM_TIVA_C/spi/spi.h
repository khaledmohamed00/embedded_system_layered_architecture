#ifndef __SPI_H__
#define __SPI_H__
#include "TM4C123GH6PM.h"
#include "tm4c123gh6pm.h"


void spi_init(void);
void writeSPI(uint8_t data);
unsigned char readSPI(void);
uint8_t  read_writeSPI(uint8_t data);
#endif // __I2C_H__
