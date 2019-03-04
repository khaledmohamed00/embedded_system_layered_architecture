/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_register.h"

/* IO Pins */
void DIO_SetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= xPORTD) && (u8PinIdCopy <= PIN7))
	{
		if (u8PinValCopy == HIGH)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case xPORTA: SET_BIT(PORTA_Register,u8PinIdCopy); break;
				case xPORTB: SET_BIT(PORTB_Register,u8PinIdCopy); break;
				case xPORTC: SET_BIT(PORTC_Register,u8PinIdCopy); break;
				case xPORTD: SET_BIT(PORTD_Register,u8PinIdCopy); break;
			}
		
		}
		
		else if (u8PinValCopy == LOW)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case xPORTA: CLR_BIT(PORTA_Register,u8PinIdCopy); break;
				case xPORTB: CLR_BIT(PORTB_Register,u8PinIdCopy); break;
				case xPORTC: CLR_BIT(PORTC_Register,u8PinIdCopy); break;
				case xPORTD: CLR_BIT(PORTD_Register,u8PinIdCopy); break;
			}
		}
	
		else
		{
			/* Do nothing, Wrong value to set */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

u8 DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy)
{
	/* Define Local Variable to get the BIT Value */
	u8 u8ResultLocal;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= xPORTD) && (u8PinIdCopy <= PIN7))
	{
		/* Check on the Required PORT Number */
		switch (u8PortIdCopy)
		{
			case xPORTA: u8ResultLocal= GET_BIT(PINA_Register,u8PinIdCopy); break;
			case xPORTB: u8ResultLocal= GET_BIT(PINB_Register,u8PinIdCopy); break;
			case xPORTC: u8ResultLocal= GET_BIT(PINC_Register,u8PinIdCopy); break;
			case xPORTD: u8ResultLocal= GET_BIT(PIND_Register,u8PinIdCopy); break;
		}
	}
	
	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		u8ResultLocal = 0xFF;
	}
	
	return u8ResultLocal;
}

void DIO_SetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= xPORTD) && (u8PinIdCopy <= PIN7))
	{
		if ( u8PinDirCopy == OUTPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case xPORTA: SET_BIT(DDRA_Register,u8PinIdCopy); break;
				case xPORTB: SET_BIT(DDRB_Register,u8PinIdCopy); break;
				case xPORTC: SET_BIT(DDRC_Register,u8PinIdCopy); break;
				case xPORTD: SET_BIT(DDRD_Register,u8PinIdCopy); break;
			}
		}
		
		else if ( u8PinDirCopy == INPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case xPORTA: CLR_BIT(DDRA_Register,u8PinIdCopy); break;
				case xPORTB: CLR_BIT(DDRB_Register,u8PinIdCopy); break;
				case xPORTC: CLR_BIT(DDRC_Register,u8PinIdCopy); break;
				case xPORTD: CLR_BIT(DDRD_Register,u8PinIdCopy); break;
			}
		}
		
		else
		{
			/* Do nothing, Wrong Direction Required */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}


/* IO Ports */
void DIO_SetPortDirection (u8 u8PortId, u8 u8PortDir)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
		case     xPORTA: DDRA_Register = u8PortDir; break;
		case     xPORTB: DDRB_Register = u8PortDir; break;
		case     xPORTC: DDRC_Register = u8PortDir; break;
		case     xPORTD: DDRD_Register = u8PortDir; break;
		default: /* Wrong Port ID */       break;
	}
}

void DIO_SetPortValue (u8 u8PortId, u8 u8PortVal)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
		case     xPORTA: PORTA_Register = u8PortVal; break;
		case     xPORTB: PORTB_Register = u8PortVal; break;
		case     xPORTC: PORTC_Register = u8PortVal; break;
		case     xPORTD: PORTD_Register = u8PortVal; break;
		default: /* Wrong Port ID */        break;
	}
}
