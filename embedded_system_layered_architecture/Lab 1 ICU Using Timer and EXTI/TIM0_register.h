#ifndef _TIMER_REGISTER_H
#define _TIMER_REGISTER_H

#define TCCR0_Register    *((volatile u8*) 0x53)
#define TCNT0_Register    *((volatile u8*) 0x52)
#define OCR0_Register     *((volatile u8*) 0x5C)
#define TIMSK_Register    *((volatile u8*) 0x59)
#define TIFR_Register     *((volatile u8*) 0x58)

#endif