 


#ifndef I2C_MASTER_H_FILE_H_					
#define I2C_MASTER_H_FILE_H_

#define F_CPU 8000000UL							
#include <avr/io.h>								
#include <util/delay.h>							
#include <math.h>								
#define SCL_CLK 100000L							/* Define SCL clock frequency */
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) /* Define bit rate */

void I2C_Init();								
uint8_t  I2C_Start(char);						
uint8_t  I2C_Repeated_Start(char);				
void I2C_Stop();								
void I2C_Start_Wait(char);						
uint8_t  I2C_Write(char);						
char I2C_Read_Ack();							
char I2C_Read_Nack();							


#endif											