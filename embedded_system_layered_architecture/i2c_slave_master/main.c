#include<avr/io.h>
#include"i2c.h"

void TWI_init_slave(void) // Function to initilaize slave
{
    TWAR=0x20;    // Fill slave address to TWAR
} 

void TWI_match_read_slave(void) //Function to match the slave address and slave dirction bit(read)
{
    while((TWSR & 0xF8)!= 0x60)  // Loop till correct acknoledgement have been received
    {
        // Get acknowlegement, Enable TWI, Clear TWI interrupt flag
        TWCR=(1<<TWEA)|(1<<TWEN)|(1<<TWINT);    
        while (!(TWCR & (1<<TWINT)));  // Wait for TWINT flag
    }
    PORTA=0xff;
} 

void TWI_read_slave(void)
{
    // Clear TWI interrupt flag,Get acknowlegement, Enable TWI
    TWCR= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);    
    while (!(TWCR & (1<<TWINT)));    // Wait for TWINT flag
    while((TWSR & 0xF8)!=0x80);        // Wait for acknowledgement
    unsigned char recv_data=TWDR;                    // Get value from TWDR
    PORTA=recv_data;                // send the receive value on PORTB
}


int main(void){
/*DDRD=0xff;

i2c_init_slave(0x20);

i2c_listen_slave();
PORTD=0xf0;
PORTD=i2c_receive_slave_ack(0);
PORTD=i2c_receive_slave_ack(1);*/
DDRA=0xff;
TWI_init_slave();
TWI_match_read_slave();
TWI_read_slave();

while(1){}
return 0;

}

