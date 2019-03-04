/*
 * DIO.c
 *
 *  Created on: Aug 26, 2017
 *      Author: Mohamed Waleed
 */

/*
 * This file contains the Implementation of the functions
 * and the others which is not preferred to be used by the user
 */


#include "STD_Types.h"
#include "utilss.h"
#include "DIO.h"



/*
 * Define DIO Registers
 * from data sheet from Section Register Summary
 */

#define DDRA *((u8*)0x3A)
#define PINA *((u8*)0x39)
#define PORTA *((u8*)0x3B)

#define DDRB *((u8*)0x37)
#define PINB *((u8*)0x36)
#define PORTB *((u8*)0x38)

#define DDRC *((u8*)0x34)
#define PINC *((u8*)0x33)
#define PORTC *((u8*)0x35)

#define DDRD *((u8*)0x31)
#define PIND *((u8*)0x30)
#define PORTD *((u8*)0x32)



/*******************************************************************************************
 *
 *    This function is to set the direction of each that it could be O/P pin or I/P pin
 *    And it takes two input parameters :
 *	  the first argument is the pin number which the user want to set its direction
 *	  the Second argument is the value (1 || 0) to set it to the selected pin
 *    its return type is void that means it has no return value
 *
********************************************************************************************/

extern void DIO_voidSetPinDirection(u8 Copy_u8PinNum, u8 Copy_u8PinValue )
{
	if( (Copy_u8PinNum>=0 && Copy_u8PinNum<=31) &&  (Copy_u8PinValue==0 || Copy_u8PinValue==1) )
	{
		//here is a switch case to specify which pin was passed to the function and assign the value to it
		if(Copy_u8PinNum/8==0)
		{
			assign_bit(DDRA,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		else if(Copy_u8PinNum/8==1)
		{
			assign_bit(DDRB,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		else if(Copy_u8PinNum/8==2)
		{
			assign_bit(DDRC,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		else if(Copy_u8PinNum/8==3)
		{
			assign_bit(DDRD,Copy_u8PinNum%8,Copy_u8PinValue);
		}
	}
}

/*******************************************************************************************
 *
 *
 *
 *
********************************************************************************************/


extern void DIO_voidSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8PortValue)
{
	if(Copy_u8PortID==PORTA_ID)
	{
		DDRA=Copy_u8PortValue;
	}
	else if (Copy_u8PortID==PORTB_ID)
	{
		DDRB=Copy_u8PortValue;
	}
	else if (Copy_u8PortID==PORTC_ID)
	{
		DDRC=Copy_u8PortValue;
	}
	else if (Copy_u8PortID==PORTD_ID)
	{
		DDRD=Copy_u8PortValue;
	}
	else
	{

	}
}

/*******************************************************************************************
 *
 *
 *
 *
********************************************************************************************/

extern void DIO_voidWritePinValue(u8 Copy_u8PinNum, u8 Copy_u8PinValue)
{
	/*
	*in this function we are going to take 2 passing parameters
	*the 1st one is the number of the PIN
	*the 2nd one is the value that needed to be assigned to the pre-specified PIN
	*	its return type is void that means it has no return value
	*/

	if( (Copy_u8PinNum>=0 && Copy_u8PinNum<=31) &&  (Copy_u8PinValue==0 || Copy_u8PinValue==1) )
	{
		//the switch case to specify which pin was selected by the user
		if((Copy_u8PinNum/8)==0)
		{
			assign_bit(PORTA,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		else if((Copy_u8PinNum/8)==1)
		{
			assign_bit(PORTB,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		else if((Copy_u8PinNum)/8==2)
		{
			assign_bit(PORTC,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		else if((Copy_u8PinNum/8)==3)
		{
			assign_bit(PORTD,Copy_u8PinNum%8,Copy_u8PinValue);
		}
	}

}

/***********************************************************************/

extern void DIO_voidWritePortValue(u8 Copy_u8PortID, u8 Copy_u8PortValue)
{
	if(Copy_u8PortID==PORTA_ID)
	{
		PORTA=Copy_u8PortValue;
	}
	else if (Copy_u8PortID==PORTB_ID)
	{
		PORTB=Copy_u8PortValue;
	}
	else if (Copy_u8PortID==PORTC_ID)
	{
		PORTC=Copy_u8PortValue;
	}
	else if (Copy_u8PortID==PORTD_ID)
	{
		PORTD=Copy_u8PortValue;
	}
	else
	{

	}
}

//=======================================================================================
extern u8 DIO_u8ReadPinValue(u8 Copy_u8PinNum)
{
	/*
		*in this function we are going to take 1 passing parameter
		*the passing parameter is the number of the PIN
		*	its return type is u8 that means it has a return value with data type (u8)
		*/

	//a u8 variable to store the read value and return it
	u8 Local_u8ReturnValue;
	if( Copy_u8PinNum>=0 && Copy_u8PinNum<=31)
		{
			if(Copy_u8PinNum/8==0)
			{
				Local_u8ReturnValue=get_bit(PINA,Copy_u8PinNum%8);
			}
			else if(Copy_u8PinNum/8==1)
			{
				Local_u8ReturnValue=get_bit(PINB,Copy_u8PinNum%8);
			}
			else if(Copy_u8PinNum/8==2)
			{
				Local_u8ReturnValue=get_bit(PINC,Copy_u8PinNum%8);
			}
			else if(Copy_u8PinNum/8==3)
			{
				Local_u8ReturnValue=get_bit(PIND,Copy_u8PinNum%8);
			}
		}

	//return the output of the selected pin
	return Local_u8ReturnValue;
}

/*******************************************************************************************/
extern u8 DIO_u8ReadPortValue(u8 Copy_u8PortID)
{
	if(Copy_u8PortID==PORTA_ID)
	{
		return PINA;
	}
	else if (Copy_u8PortID==PORTB_ID)
	{
		return PINB;
	}
	else if (Copy_u8PortID==PORTC_ID)
	{
		return PINC;
	}
	else if (Copy_u8PortID==PORTD_ID)
	{
		return PIND;
	}
	else
	{
	}
	return -1;
}












