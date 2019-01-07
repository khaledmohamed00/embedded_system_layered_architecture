/* Board Support Package */

#include <bsp.h>

__attribute__((naked)) void assert_failed (char const *file, int line) {
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}



// Subroutine to initialize port F pins for input and output

// PF4 is input SW1 and PF2 is output Blue LED

// Inputs: None

// Outputs: None

// Notes: ...

void PortF_Init(void){ volatile unsigned long delay;

  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F

  delay = SYSCTL_RCGC2_R;           // allow time for clock to start

  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F

  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0

  // only PF0 needs to be unlocked, other bits can't be locked

  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF

  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0

  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out

  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0

  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4

  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0

}

void PLL_Init(void){

  // 0) Use RCC2

  SYSCTL_RCC2_R |=  0x80000000;  // USERCC2

  // 1) bypass PLL while initializing

  SYSCTL_RCC2_R |=  0x00000800;  // BYPASS2, PLL bypass

  // 2) select the crystal value and oscillator source

  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field, bits 10-6

                 + 0x00000540;   // 10101, configure for 16 MHz crystal

  SYSCTL_RCC2_R &= ~0x00000070;  // configure for main oscillator source

  // 3) activate PLL by clearing PWRDN

  SYSCTL_RCC2_R &= ~0x00002000;

  // 4) set the desired system divider

  SYSCTL_RCC2_R |= 0x40000000;   // use 400 MHz PLL

  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // clear system clock divider

                  + (4<<22);      // configure for 80 MHz clock

  // 5) wait for the PLL to lock by polling PLLLRIS

  while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit

  // 6) enable use of PLL by clearing BYPASS

  SYSCTL_RCC2_R &= ~0x00000800;

}


void SysTick_Init(void){

  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup

  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock

}

// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)

void SysTick_Wait(unsigned long delay){

  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait

  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears

  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag

  }

}

// 800000*12.5ns equals 10ms

void SysTick_Wait10ms(unsigned long delay){

  unsigned long i;

  for(i=0; i<delay; i++){

    SysTick_Wait(800000);  // wait 10ms

  }

}


void SysTick_Handler(void) {
    //GPIOF_AHB->DATA_Bits[LED_BLUE] ^= LED_BLUE;
    GPIO_PORTF_DATA_R ^= (1<<2);
}


void PortF_AHB_CMSIS_Init(void){

    SYSCTL->RCGCGPIO  |= (1U << 5); /* enable Run mode for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);



}

void SysTick_CMSIS_Init(void){

    SysTick->LOAD = SYS_CLOCK_HZ/2U - 1U;
    SysTick->VAL  = 0U;
    SysTick->CTRL = (1U << 2) | (1U << 1) | 1U;

}







