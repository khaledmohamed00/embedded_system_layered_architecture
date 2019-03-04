 


#include "I2C_Master_interface.h"								

void I2C_Init()												
{
	TWBR = BITRATE(TWSR = 0x00);							
}	


uint8_t I2C_Start(char slave_write_address)						/* I2C start function */
{
	uint8_t status;											
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;									
	if (status != 0x08)										
	return 0;												
	TWDR = slave_write_address;								
	TWCR = (1<<TWEN)|(1<<TWINT);							
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;										
	if (status == 0x18)										
	return 1;												
	if (status == 0x20)										
	return 2;												
	else
	return 3;												
}

uint8_t I2C_Repeated_Start(char slave_read_address)			/* I2C repeated start function */
{
	uint8_t status;											
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;									
	if (status != 0x10)										
	return 0;												
	TWDR = slave_read_address;								
	TWCR = (1<<TWEN)|(1<<TWINT);							
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;									
	if (status == 0x40)										
	return 1;												
	if (status == 0x20)										
	return 2;												
	else
	return 3;												
}

void I2C_Stop()												/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					
	while(TWCR & (1<<TWSTO));								
}

void I2C_Start_Wait(char slave_write_address)				/* I2C start wait function */
{
	uint8_t status;											
	while (1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);				
		while (!(TWCR & (1<<TWINT)));						
		status = TWSR & 0xF8;								
		if (status != 0x08)									
		continue;											
		TWDR = slave_write_address;							
		TWCR = (1<<TWEN)|(1<<TWINT);						
		while (!(TWCR & (1<<TWINT)));						
		status = TWSR & 0xF8;								
		if (status != 0x18 )								
		{
			I2C_Stop();										
			continue;										
		}
		break;												
	}
}

uint8_t I2C_Write(char data)								/* I2C write function */
{
	uint8_t status;											
	TWDR = data;											
	TWCR = (1<<TWEN)|(1<<TWINT);							
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;									
	if (status == 0x28)										
	return 0;												
	if (status == 0x30)										
	return 1;												
	else
	return 2;												/* Else return 2 to indicate data transmission failed */
}

char I2C_Read_Ack()										/* I2C read ack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					
	while (!(TWCR & (1<<TWINT)));							
	return TWDR;											
}	

char I2C_Read_Nack()										/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);								
	while (!(TWCR & (1<<TWINT)));							
	return TWDR;											
}	
