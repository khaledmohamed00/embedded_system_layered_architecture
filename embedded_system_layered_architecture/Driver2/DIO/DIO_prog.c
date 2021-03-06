#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_reg.h"
#include "DIO_int.h"

/*********************************************************************************************************************************/
/**********************************************DIO_Registers**********************************************************************/
/********************************************************************************************************************************/
volatile u8 *PORT_Direction[4]={DDRA_Register,DDRB_Register,DDRC_Register,DDRD_Register};
volatile u8 *PORT_Input[4]=    {PINA_Register,PINB_Register,PINC_Register,PIND_Register};
volatile u8 *PORT_Output[4]=   {PORTA_Register,PORTB_Register,PORTC_Register,PORTD_Register};




/***********************************************IO_Pins*****************************************************************************/


/**************************************************DIO_u8SetPinValue*******************************************************************************/
/**********************************************************************************************************************************/
/**********************************************************************************************************************************/
u8 DIO_u8SetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy){

if(u8PortIdCopy<=PORTD && u8PinIdCopy<=PIN7){

if(u8PinValCopy==HIGH){
SET_BIT(*PORT_Output[u8PortIdCopy],u8PinIdCopy);

}
else
{
CLR_BIT(*PORT_Output[u8PortIdCopy],u8PinIdCopy);
}

return SUCCESS;
}

else{

return ERROR;

}



}


/**************************************************DIO_u8GetPinValue*******************************************************************************/
/**********************************************************************************************************************************/
/**********************************************************************************************************************************/

u8 DIO_u8GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy,u8* u8ptrPinValCopy){


if(u8PortIdCopy<=PORTD && u8PinIdCopy<=PIN7){
*u8ptrPinValCopy=GET_BIT(*PORT_Input[u8PortIdCopy],u8PinIdCopy);
return SUCCESS;
}

else{

return ERROR;

}


}

u8 DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy){


if(u8PortIdCopy<=PORTD && u8PinIdCopy<=PIN7){
GET_BIT(*PORT_Input[u8PortIdCopy],u8PinIdCopy);
return GET_BIT(*PORT_Input[u8PortIdCopy],u8PinIdCopy);
}

else{

return ERROR;

}


}



/**************************************************DIO_u8SetPinDirection*******************************************************************************/
/**********************************************************************************************************************************/
/**********************************************************************************************************************************/


u8 DIO_u8SetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy){


if(u8PortIdCopy<=PORTD && u8PinIdCopy<=PIN7){

if(u8PinDirCopy==HIGH)
{SET_BIT(*PORT_Direction[u8PortIdCopy],u8PinIdCopy);
}
else
{
CLR_BIT(*PORT_Direction[u8PortIdCopy],u8PinIdCopy);
}

return SUCCESS;

}

else{

return ERROR;

}


}



/***********************************************IO_PORTS*****************************************************************************/


/**************************************************DIO_u8SetPortDirection*******************************************************************************/
/**********************************************************************************************************************************/
/**********************************************************************************************************************************/



u8 DIO_u8SetPortDirection (u8 u8PortIdCopy, u8 u8PortDirCopy){

if(u8PortIdCopy<=PORTD){

*PORT_Direction[u8PortIdCopy]=u8PortDirCopy;


return SUCCESS;

}

else{

return ERROR;

}

}

/**************************************************DIO_u8SetPortValue*******************************************************************************/
/**********************************************************************************************************************************/
/**********************************************************************************************************************************/



u8 DIO_u8SetPortValue(u8 u8PortIdCopy, u8 u8PortValCopy){
if(u8PortIdCopy<=PORTD && u8PortValCopy<=0xff){

*PORT_Output[u8PortIdCopy]=u8PortValCopy;

return SUCCESS;

}

else{

return ERROR;

}


}







