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
extern unsigned long H,L;


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



// L range: 8000,16000,24000,32000,40000,48000,56000,64000,72000
// power:   10%    20%   30%   40%   50%   60%   70%   80%   90%
void GPIOPortF_IRQHandler(void){
    if(GPIO_PORTF_RIS_R&0x01){  // SW2 touch
        GPIO_PORTF_ICR_R = 0x01;  // acknowledge flag0
        if(L>8000) L = L-8000;    // slow down
      }
      if(GPIO_PORTF_RIS_R&0x10){  // SW1 touch
        GPIO_PORTF_ICR_R = 0x10;  // acknowledge flag4
        if(L<72000) L = L+8000;   // speed up
      }
      H = 80000-L; // constant period of 1ms, variable duty cycle
}



void SysTick_Handler(void){
  if(GPIO_PORTF_DATA_R&(1<<2)){   // toggle PA5
    GPIO_PORTF_DATA_R &= ~(1<<2); // make PA5 low
    NVIC_ST_RELOAD_R = L-1;     // reload value for low phase
  } else{
    GPIO_PORTF_DATA_R |= (1<<2);  // make PA5 high
    NVIC_ST_RELOAD_R = H-1;     // reload value for high phase
  }
}

void Switch_Init(void){  unsigned long volatile delay;
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
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4,PF0 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4,PF0 is not both edges
  GPIO_PORTF_IEV_R &= ~0x11;    //     PF4,PF0 falling edge event
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flags 4,0
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4,PF0
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000; // (g) priority 2
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
}

void Motor_Init(void){

  NVIC_ST_CTRL_R = 0;           // disable SysTick during setup
  NVIC_ST_RELOAD_R = L-1;       // reload value for 500us
  NVIC_ST_CURRENT_R = 0;        // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
  NVIC_ST_CTRL_R = 0x00000007;  // enable with core clock and interrupts
}

