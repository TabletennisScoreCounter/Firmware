/*
 * LCDDisplayDriver.c
 *
 *  Created on: 2018/02/10
 *      Author: Shuji
 */

#define RTOS_USE 1

#include "LCDDisplayDriver.h"
#include "i2c.h"

#if RTOS_USE == 1
#include <cmsis_os.h>
#endif


#define DEVICE_ADDRESS 0x7C
#define COMMAND_ADDRESS 0x00
#define TIME_OUT 100

#define DATA_ADDRESS 0x40

#define I2CHANDLE hi2c1

static HAL_StatusTypeDef memoryWriteByte(uint8_t address, uint8_t data);
static HAL_StatusTypeDef memoryWriteBytes(uint8_t address, uint8_t* pdata, uint16_t length);
static void delay_ms(int milisec);


void delay_ms(int milisec)
{
#if RTOS_USE == 1
  osDelay(milisec);
#else
  HAL_Delay(milisec);
#endif
}
HAL_StatusTypeDef memoryWriteByte(uint8_t address, uint8_t data)
{
  uint8_t dataToWrite[] = {data};

  return memoryWriteBytes(address, dataToWrite, sizeof(dataToWrite));
}
HAL_StatusTypeDef memoryWriteBytes(uint8_t address, uint8_t* pdata, uint16_t length)
{
  return HAL_I2C_Mem_Write(&I2CHANDLE, DEVICE_ADDRESS, address, 1, pdata, length, TIME_OUT);
}
LCDDisplayStatus_t Initialize_LCDDisplayDriver()
{
  LCDDisplayStatus_t result = LCDDISPLAY_OK;

  HAL_StatusTypeDef writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x38);

  if(writeResult == HAL_OK){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x39);
  }

  if(writeResult == HAL_OK){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x14);
  }

  if(writeResult == HAL_OK){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x7A);
  }

  if(writeResult == HAL_OK){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x54);
  }

  if(writeResult == HAL_OK){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x6C);
    delay_ms(200);
  }

  if(writeResult == HAL_OK){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x38);
  }

  if(writeResult == HAL_OK){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x0C);
  }

  if(writeResult == HAL_OK){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x01);
  }

  if(writeResult == HAL_OK){
    delay_ms(2);
  }else{
    result = LCDDISPLAY_ERROR;
  }

  return result;
}
LCDDisplayStatus_t SetChar_LCDDisplayDriver(uint8_t* str, uint8_t length, uint8_t line)
{
  LCDDisplayStatus_t result = LCDDISPLAY_OK;

  HAL_StatusTypeDef writeResult = HAL_OK;

  if(line == 1){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x80);
  }
  else if(line == 2){
    writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x40 | 0x80);
  }

  if(writeResult == HAL_OK){
    memoryWriteBytes(DATA_ADDRESS, str, length);
    delay_ms(2);
  }
  else{
    result = LCDDISPLAY_ERROR;
  }

  return result;
}
LCDDisplayStatus_t ClearChar_LCDDisplayDriver()
{
  LCDDisplayStatus_t result = LCDDISPLAY_OK;

  HAL_StatusTypeDef writeResult = memoryWriteByte(COMMAND_ADDRESS, 0x01);
  delay_ms(2);

  if(writeResult != HAL_OK){
    result = LCDDISPLAY_ERROR;
  }

  return result;
}
