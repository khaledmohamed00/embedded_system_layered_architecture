#ifndef ADC_REGISTER_H
#define ADC_REGISTER_H


#define ADMUX_Reg 	*((volatile u8*)0x27) 	// ADC Multiplexer Register
#define ADCSRA_Reg 	*((volatile u8*)0x26) 	// ADC Control And Status Register
#define ADCH_Reg 	*((volatile u8*)0x25) 		// ADC High Register
#define ADCL_Reg 	*((volatile u8*)0x24) 		// ADC Low Register
#define ADC             *((volatile u16*)0x24)          //ADC 16 bit high and low register




#endif
