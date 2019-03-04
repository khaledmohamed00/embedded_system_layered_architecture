#include"STD_TYPES.h"
#include "IIC.h"
#include "UART_IO_int.h"
#include"eeprom.h"
#include "IIC_private.h"
void EEPROM_Init(void)
{
  I2C_Init();
}

u8 EEPROM_WriteByte(u16 addr, u8 data,u8 stop)
{
  u8 state = 0;
  u8 _3MSBAddr = 0;

  // Start TWI
  TWIStart();
  // Get State
  state = TWIGetStatus();
  // Check if TWI Start
  if (state != TW_START)
  {USART_SendString("TW_START_Erro");
    USART_SendString("\r\n");
      //PORTA |= 0x01;
    return 0;
  }
  
  _3MSBAddr = ((u8) ((addr & 0x0700) >> 7));
   TWIWrite(0xA0|_3MSBAddr);
  //TWIWrite(0xA0);
  // Get Status
  state = TWIGetStatus();
  // Check if it is TW_MT_SLA_ACK
  if (state != TW_MT_SLA_ACK)
  {
    USART_SendString("TW_MT_SLA_ACK_Erro");
    USART_SendString("\r\n");
    //PORTA |= 0x02;
    return 0;
  }

  // Write the Rest of Location Address(8 Bits)
  TWIWrite((u8) addr);

  // Get State
  state = TWIGetStatus();

  // check if it is TW_MT_DATA_ACK
  if (state != TW_MT_DATA_ACK)
  {
    USART_SendString("TW_MT_DATA_ACK_Erro");
    USART_SendString("\r\n");
   
   //PORTA |= 0x04;
    return 0;
  }

  // Send Data
  TWIWrite(data);

  // Get Status
  state = TWIGetStatus();

  // Check if it is TW_MT_DATA_ACK
  if (state != TW_MT_DATA_ACK)
  {
    USART_SendString("TW_MT_DATA_ACK_Erro");
    USART_SendString("\r\n");
      // PORTA |= 0x02;
    return 0;
  }

  // TWI Stop
  if(stop==1)
  {TWIStop();
  }
  // Return Done
  return 1;
}

u8 EEPROM_ReadByte(u16 addr, u8 *data,u8 stop)
{
  u8 state = 0;
  u8 _3MSBAddr = 0;

  // Start TWI
  TWIStart();

  // Get State
  state = TWIGetStatus();

  // Check if TWI Start
  if (state != TW_START)
    {USART_SendString("TW_START_Erro");
    USART_SendString("\r\n");
    return 0;
    }

  
  _3MSBAddr = ((u8) ((addr & 0x0700) >> 7));
   TWIWrite(0xA0|_3MSBAddr);
  //TWIWrite(0xA0);

  // Get Status
  state = TWIGetStatus();

  // Check if it is TW_MT_SLA_ACK
  if (state != TW_MT_SLA_ACK)
    {USART_SendString("TW_MT_SLA_ACK_Erro");
    USART_SendString("\r\n");

      return 2;
     
     }
  // Write the Rest of Location Address(8 Bits)
  TWIWrite((u8) addr);

  // Get State
  state = TWIGetStatus();

  // check if it is TW_MT_DATA_ACK
  if (state != TW_MT_DATA_ACK)
    {USART_SendString("TW_MT_DATA_ACK_Erro");
    USART_SendString("\r\n");
      return 3;
    }
  // Now The Master Will Be Master Reciever

  // Now we need to Send Start Bit Again
  // Start TWI
  TWIStart();

  // Get State
  state = TWIGetStatus();

  // Check if TW_REP_START
  if (state != TW_REP_START)
    {USART_SendString("TW_REP_START_Erro");
     USART_SendString("\r\n");

      return 4;
    }
  
  _3MSBAddr = ((u8) ((addr & 0x0700) >> 7));
   TWIWrite(0xA0|_3MSBAddr|1);
//  TWIWrite(0xA0 | 1);
  // Get Status
  state = TWIGetStatus();

  // Check if it is TW_MR_SLA_ACK
  if (state != TW_MR_SLA_ACK)
    {USART_SendString("TW_MR_SLA_ACK_Erro");
     USART_SendString("\r\n");

      return 5;
    }
  // Read Data
  // *data = TWIReadNACK();
  *data = TWIReadACK();

  // Get Status
  state = TWIGetStatus();

  // Check if it is
  if (state != TW_MR_DATA_ACK)
  {
    USART_SendString("TW_MR_DATA_ACK_Erro");
     USART_SendString("\r\n");
    return 6;
  }
  // TWI Stop
 if(stop==1)
  {TWIStop();
  }

  // Return Done
  return 1;
}


