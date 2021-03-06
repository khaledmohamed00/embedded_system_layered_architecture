
#ifndef _DIO_INT_H
#define _DIO_INT_H


/* Port Defines */
#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3

/* PIN Defines */
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1

/* PIN Value Options */
#define HIGH   1
#define LOW    0

/*status codes*/
#define ERROR 0xff
#define SUCCESS 0x00

/* IO Pins */
u8 DIO_u8SetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy);

u8 DIO_u8GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy,u8* u8ptrPinValCopy);

u8 DIO_u8SetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy);

/* IO Ports */
u8 DIO_u8SetPortDirection (u8 u8PortId, u8 u8PortDir);

u8 DIO_u8SetPortValue     (u8 u8PortId, u8 u8PortVal);





#endif
