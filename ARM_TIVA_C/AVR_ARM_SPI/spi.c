/* Board Support Package */

#include <spi.h>
__attribute__((naked)) void assert_failed (char const *file, int line) {
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}
uint8_t  readSPI(void)
{ while( ((SSI2->SR & (1<<3)) == 0));
 return  (unsigned char)SSI2->DR ;

}

uint8_t  read_writeSPI(uint8_t data){
    SSI2->DR = data;
    while( ((SSI2->SR & (1<<4)) == 1));
  //  while( ((SSI2->SR & (1<<3)) == 0));
    return (uint8_t) SSI2->DR;
}
void writeSPI(uint8_t data)
{
  SSI2->DR = data;
  while( ((SSI2->SR & (1<<0)) == 0));
}
void spi_init(void){
    //Step 1: Enable the SSI module using the RCGCSSI register [pg. 321]
     //I am using SSI2
     SYSCTL->RCGCSSI =  (1<<2);

     //Step 2: Enable the clock to the appropriate GPIO module via the RCGCGPIO register [pg. 315]
     //I am using Port B which is represented by bit 1
     SYSCTL->RCGCGPIO = (1<<1);

     //Step 3: Set the GPIO AFSEL bits for the appropriate pins [pg. 632]
     //I am using PB 4,5,6,7
     //GPIOB->AFSEL |= (1<<4)|(1<<6)|(1<<7)|(1<<5);
     GPIOB->AFSEL |= (1<<4)|(1<<6)|(1<<7);
     //To take control of the CS pin. First disable the alternate function of the pin
     GPIOB->AFSEL &= ~(1<<5);

     //Step 4: Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate pins
     //A pin may have several alternate functions, here I select which alternate function I need
     //The SSI2 functions for pin PB 4,5,6,7 are located at 2 see Table 21-5 [pg. 1143]
     GPIOB->PCTL |= (2<<16)|(2<<20)|(2<<24)|(2<<28);

     //Pins will be used as digital pins => I must enable them. SSI IS A DIGITAL SIGNAL
     GPIOB->DEN |= (1<<4)|(1<<6)|(1<<7)|(1<<5);
     GPIOB->DIR |= (1<<5);

     //For each of the fram formats, the SSI is configured using the following steps:
     //Step 1: Ensure that the SSE bit in the SSICR1 register is clear before making any configuration changes.
     SSI2->CR1 &= ~(1<<1);

     //Step 2: Select whether the SSI is a master or slave
     SSI2->CR1 = 0x00000000;

     //Step 3: Configure the SSI clock source by writing to the SSICC register
     SSI2->CC =0x00;

     //Step 4: Configure the clock prescale divisor by writing the SSICPSR register
     SSI2->CPSR = 128; //WHY 1.6mHZ

     //Step 5: Write the SSICR0 register with the following configuration
     SSI2->CR0 = (0x7<<0);

     //BOTTOM TWO LINES ARE FOR MODE 1,1. REMOVE THEM IF YOU WANT TO CHOOSE MODE 0,0
     //SSI2->CR0 |= (1<<6);
     //SSI2->CR0 |= (1<<7);

     //Step 6: Optionally, configure the uDMA channel and enable the DMA options(s) in the SSIDMACTL register

     //Step 7: Enalbe the SSI by setting the SSE bit in the SSICR1 register
     SSI2->CR1 |= (1<<1);
     GPIOB->DATA |= (1<<5);
     GPIOB->DATA &= ~(1<<5); // SS/CS low, begin transmission


}
