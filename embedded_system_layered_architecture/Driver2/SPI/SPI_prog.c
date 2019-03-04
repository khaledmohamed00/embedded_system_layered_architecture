#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"SPI_int.h"


void spi_slave_init(void){
    DDRB &= ~((1<<5)|(1<<6)|(1<<7));   // SCK, MOSI and SS as inputs
    DDRB |= (1<<4);                    // MISO as output

    SPCR &= ~(1<<MSTR);                // Set as slave 

    SPCR |= (1<<SPE); 

}

void spi_master_init(void){
DDRB |= (1<<2)|(1<<3)|(1<<5);    // SCK, MOSI and SS as outputs
    DDRB &= ~(1<<4);                 // MISO as input

    SPCR |= (1<<MSTR);               // Set as Master
    SPCR |= (1<<SPR0)|(1<<SPR1);     // divided clock by 128
    SPCR |= (1<<SPE);                // Enable SPI
}

unsigned char spi_send_receive(unsigned char data){

SPDR = data;                 // send the data
        while(!(SPSR & (1<<SPIF)));  // wait untiltransmission is complete
         return SPDR;
} 

unsigned char SPI_SlaveReceive(void)
{
	while(!(SPSR & (1<<SPIF)));// Wait for reception complete 
	return SPDR;// Return data register 
}

void SPI_MasterTransmit(unsigned char cData)
{
	SPDR = cData;// Start transmission 
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete 
}
