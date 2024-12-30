#include "LCDControl.h"

#include "AQM1602.h"
#include "MiddlewareCommon.h"
#include "i2c.h"
#include <cmsis_os.h>
#include <stdbool.h>
#include <string.h>

#define I2CHANDLE hi2c1

#define I2CTIMEOUT 1000

static AQM1602ResultTypeDef_t i2cWrite(uint8_t _slaveAddress, const uint8_t* _data, uint16_t _length);
static void delay_ms(uint32_t milisecond);

static AQM1602InteraceTypeDef_t interface = {
  .i2cWrite = i2cWrite,
  .delay_ms = delay_ms
};
static bool i2cTransmitEventFlg = false;

MiddlewareResultTypeDef_t LCDControl_Init()
{
  MiddlewareResultTypeDef_t result = Middleware_OK;

  AQM1602ResultTypeDef_t devResult = AQM1602_SampleInitialize(&interface);

  if(devResult != AQM1602_OK){
    result = Middleware_NG;
  }

  return result;
}
MiddlewareResultTypeDef_t LCDControl_RequestPrint(const char* _line1Str, const char* _line2Str)
{
  MiddlewareResultTypeDef_t result = Middleware_OK;

  AQM1602ResultTypeDef_t devResult = AQM1602_SendCharData(&interface, (uint8_t*)_line1Str, strlen(_line1Str));
}
static AQM1602ResultTypeDef_t i2cWrite(uint8_t _slaveAddress, const uint8_t* _data, uint16_t _length)
{
  i2cTransmitEventFlg = false;

  AQM1602ResultTypeDef_t result = AQM1602_OK;

  if(HAL_I2C_Master_Transmit_IT(&I2CHANDLE, _slaveAddress, (uint8_t*)_data, _length) != HAL_OK){
    result = AQM1602_NG;
  }

  uint16_t i2cTimeoutCnt = 0;

  while(!i2cTransmitEventFlg && result == AQM1602_OK){
    if(++i2cTimeoutCnt > I2CTIMEOUT){
      result = AQM1602_NG;
      break;
    }
    osDelay(1);
  }

  return result;
}
static void delay_ms(uint32_t milisecond)
{
  osDelay(milisecond);
}
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  if(hi2c == &I2CHANDLE){
    i2cTransmitEventFlg = true;
  }
}
