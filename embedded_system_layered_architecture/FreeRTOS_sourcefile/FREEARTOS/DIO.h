/*
 * DIO.h
 *
 *  Created on: Aug 26, 2017
 *      Author: Mohamed Waleed
 */

 
#ifndef DIO_H_
#define DIO_H_

/*
 * This file contains the prototypes of the functions
 * and the defines which will be used by the user of this driver
 */

/*******************************************************************************************
*
 * Define high & low  values to apply one or zero
*
********************************************************************************************/

#define DIO_u8LOW 0
#define DIO_u8HIGH 1

/*******************************************************************************************
*
*  Define pin output and pin input to choose the direction of the pin
*
********************************************************************************************/

#define DIO_u8PinIp 0
#define DIO_u8PinOp 1


/*******************************************************************************************
*
*   Define an ID for each Port
*
********************************************************************************************/

#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3



/*
 * define all Atmega32 pins
 */
#define DIO_u8PinA0 0
#define DIO_u8PinA1 1
#define DIO_u8PinA2 2
#define DIO_u8PinA3 3
#define DIO_u8PinA4 4
#define DIO_u8PinA5 5
#define DIO_u8PinA6 6
#define DIO_u8PinA7 7

#define DIO_u8PinB0 8
#define DIO_u8PinB1 9
#define DIO_u8PinB2 10
#define DIO_u8PinB3 11
#define DIO_u8PinB4 12
#define DIO_u8PinB5 13
#define DIO_u8PinB6 14
#define DIO_u8PinB7 15

#define DIO_u8PinC0 16
#define DIO_u8PinC1 17
#define DIO_u8PinC2 18
#define DIO_u8PinC3 19
#define DIO_u8PinC4 20
#define DIO_u8PinC5 21
#define DIO_u8PinC6 22
#define DIO_u8PinC7 23

#define DIO_u8PinD0 24
#define DIO_u8PinD1 25
#define DIO_u8PinD2 26
#define DIO_u8PinD3 27
#define DIO_u8PinD4 28
#define DIO_u8PinD5 29
#define DIO_u8PinD6 30
#define DIO_u8PinD7 31



extern void DIO_voidSetPinDirection(u8 Copy_u8PinNum, u8 Copy_u8PinValue );
extern void DIO_voidSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8PortValue);

extern void DIO_voidWritePinValue(u8 Copy_u8PinNum, u8 Copy_u8PinValue);
extern void DIO_voidWritePortValue(u8 Copy_u8PortID, u8 Copy_u8PortValue);

extern u8 DIO_u8ReadPinValue(u8 Copy_u8PinNum);
extern u8 DIO_u8ReadPortValue(u8 Copy_u8PortID);




#endif /* DIO_H_ */
