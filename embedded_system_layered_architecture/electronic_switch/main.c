#define F_CPU 8000000ul
#include<avr/io.h>
#include<util/delay.h>
#define period 5 

int main(void){
DDRD=0xff;

int i;
for(i=0;i<500;i++)
		{
			PORTD = 1;
			_delay_ms(period);
			PORTD = 2;
			_delay_ms(period);
			PORTD = 4;
			_delay_ms(period);
			PORTD = 8;
			_delay_ms(period);
		}


while(1){

}



}
