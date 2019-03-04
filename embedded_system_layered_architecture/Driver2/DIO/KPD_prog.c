#define F_CPU 8000000
#include "STD_TYPES.h"
#include "util/delay.h"
#include "DIO_int.h"
#include "KPD_interface.h"
#include "KBD_config.h"
/***************************************************************************************/

/*************************************** Constants *************************************/
/* Values of the Key Pad switches                                                      */
/* Matrix is not standard it depends on the connection between the Micro and KeyPad    */
const u8 KPD_au8SwitchVal[4][4] =
{
  {
    '7',
    '4',
    '1',
    '0' },
  {
    '8',
    '5',
    '2',
    '.' },
  {
    '9',
    '6',
    '3',
    '=' },
  {
    '/',
    'x',
    '-',
    '+' } 
};

/***************************************************************************************/


/***************************************** Macros **************************************/
//#define PORT PORTB

#define COL_INIT   0

#define COL_FIN    4

#define ROW_INIT   4

#define ROW_FIN    8

#define NOT_PRESSED    'N'
/***************************************************************************************/


/***************************************************************************************/
/* Description! Interface to get the ID of the pressed key, return 0 incase no key     */
/*              is pressed, this function doesn't handle the sitaution if 2 keys are   */
/*              pressed at the same time                               	     		   */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/


u8 KPD_u8GetPressedKey(void)
{

  u8 LOC_u8Column;

  u8 LOC_u8Row;
  u8 LOC_u8Retrun = NOT_PRESSED;
  do{
  /* Initialize the switch status to NOT Pressed                                                                     */
   LOC_u8Retrun = NOT_PRESSED;

  /* Looping on columns of the Key Pad                                                                               */
  for (LOC_u8Column = 0 + COL_INIT; LOC_u8Column < COL_FIN; LOC_u8Column++)
  {
    /* Activate the Column                                                                                           */
    DIO_u8SetPinValue(PORT, LOC_u8Column, LOW);

    /* Loop on the rows of the Key Pad                                                                               */
    for (LOC_u8Row = 0 + ROW_INIT; LOC_u8Row < ROW_FIN; LOC_u8Row++)
    {
      /* Check the status of the switch                                                                              */
      if (!DIO_GetPinValue(PORT, LOC_u8Row))
      {
        /* Get the value of the currently pressed switch                                                             */
        LOC_u8Retrun = KPD_au8SwitchVal[LOC_u8Column - COL_INIT][LOC_u8Row - ROW_INIT];

        /* Wait until the switch is released (Single Press)                                                          */
        while (!DIO_GetPinValue(PORT, LOC_u8Row))
          ;

        /* Delay to avoid bouncing                                                                                   */
        _delay_ms(10);

      }
    }

    /* Deactivate the Column                                                                                         */
    DIO_u8SetPinValue(PORT, LOC_u8Column, HIGH);
  }
  }while(LOC_u8Retrun == NOT_PRESSED);
  return LOC_u8Retrun;
}
