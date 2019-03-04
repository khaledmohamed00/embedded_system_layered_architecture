
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_int.h"
#include "ADC_register.h"

void ADC_Init (void)
{
	// ADC Enable
	SET_BIT(ADCSRA_Reg,7);

	// Prescaler Configuration as 128
	SET_BIT(ADCSRA_Reg,2);
	SET_BIT(ADCSRA_Reg,1);
	SET_BIT(ADCSRA_Reg,0);


	// Referance Voltage as AVCC with external capacitor
	CLR_BIT(ADMUX_Reg,7);
	SET_BIT(ADMUX_Reg,6);

	// ADC Data Rgith Adjustment
	CLR_BIT(ADMUX_Reg,5);
}

u16 ADCu16_Read (u8 channel)
{
	// ADC Channel Selection
	channel &= 0x07;
	ADMUX_Reg &= 0xE0;
	ADMUX_Reg |= channel;

	// Start Single Convertion
	SET_BIT(ADCSRA_Reg,6);

	//wait for the conversion
	while(!(ADCSRA_Reg & (1<<4)));

	//ADC Flag Clear
	SET_BIT(ADCSRA_Reg,4);

	return ADC;
}
