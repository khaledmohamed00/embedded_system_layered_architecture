#ifndef _MATH_H
#define _MATH_H

#define SET_BIT(REG, BITNO)  (REG) |= (1 << (BITNO))
#define CLR_BIT(REG, BITNO)  (REG) &= (~(1 << (BITNO)))
#define TOG_BIT(REG, BITNO)  (REG) ^= (1 << (BITNO))
#define GET_BIT(REG, BITNO)  (((REG) >> (BITNO)) & 0x01)


#define CONCBIT(B7,B6,B5,B4,B3,B2,B1,B0)   CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)

#define CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)  0b##B7##B6##B5##B4##B3##B2##B1##B0

#endif
