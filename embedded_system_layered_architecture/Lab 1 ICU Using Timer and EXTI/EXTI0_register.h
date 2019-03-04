#ifndef _EXTI0_REGISTER_
#define _EXTI0_REGISTER_

#define MCUCR_Register    *((u8 volatile*)0x55)
#define MCUCSR_Register   *((u8 volatile*)0x54)
#define GICR_Register     *((u8 volatile*)0x5B)
#define GIFR_Register     *((u8 volatile*)0x5A)
#define SREG_Register     *((u8 volatile*)0x5F)

#endif