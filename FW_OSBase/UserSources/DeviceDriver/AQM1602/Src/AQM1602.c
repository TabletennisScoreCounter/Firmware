#include "AQM1602.h"

#include <string.h>

#define NUM_OF_CHAR_COLUMN 16
#define MAX_DATA_SEND_SIZE (NUM_OF_CHAR_COLUMN)
#define CTRL_BYTE_SIZE 1

#define DEVICE_ADDRESS 0x7C

#define MAX_DELAY_AFTER_COMMAND 2

#define DELAY_FOR_BOOT 40

enum CTRL_Byte{
  CTRL_COMMAND = 0x00,
  CTRL_DATA = 0x40
};

enum CMD_Byte{
  CMD_CLEAR_DISPLAY = 0x01,
  CMD_RETURN_HOME = 0x02,
  CMD_ENTRY_MODE_SET = 0x04,
  CMD_DISPLAY_ON_OFF = 0x08,
  CMD_FUNCTION_SET = 0x20,
  CMD_SET_DDRAM_ADDRESS = 0x80,
  CMD_CUSOR_DISPLAY_SHIFT = 0x10,
  CMD_SET_CGRAM = 0x40,
  CMD_INTERNAL_OSC_FREQUENCY = 0x10,
  CMD_SET_ICON_ADDRESS = 0x40,
  CMD_POWER_ICON_CONTROL_CONTRAST_SET = 0x50,
  CMD_FOLLOWER_CONTROL = 0x60,
  CMD_CONTRAST_SET = 0x70
};

static AQM1602ResultTypeDef_t sendCommand(AQM1602InteraceTypeDef_t* pInterface, uint8_t _command, uint8_t _parameter);
static AQM1602ResultTypeDef_t sendData(AQM1602InteraceTypeDef_t* pInterface, uint8_t* _data, uint16_t _length);
static uint8_t parameterMask(uint8_t command);

AQM1602ResultTypeDef_t AQM1602_WaitForBoot(AQM1602InteraceTypeDef_t* pInterface)
{
  pInterface->delay_ms(DELAY_FOR_BOOT);

  return AQM1602_OK;
}
AQM1602ResultTypeDef_t AQM1602_ClearDisplay(AQM1602InteraceTypeDef_t* pInterface)
{
  AQM1602ResultTypeDef_t result = sendCommand(pInterface, CMD_CLEAR_DISPLAY, 0);
  return result;
}
AQM1602ResultTypeDef_t AQM1602_ReturnHome(AQM1602InteraceTypeDef_t* pInterface)
{
  AQM1602ResultTypeDef_t result = sendCommand(pInterface, CMD_RETURN_HOME, 0);
  return result;
}
AQM1602ResultTypeDef_t AQM1602_EntryModeSet(AQM1602InteraceTypeDef_t* pInterface, AQM1602_CursorDirectionTypeDef_t _cursorDirection, AQM1602FlagTypeDef_t _displayShift)
{
  uint8_t parameter = (uint8_t)_displayShift |
                      (uint8_t)_cursorDirection << 1;

  AQM1602ResultTypeDef_t result = sendCommand(pInterface, CMD_ENTRY_MODE_SET, parameter);
  return result;
}
AQM1602ResultTypeDef_t AQM1602_DisplayOnOff(AQM1602InteraceTypeDef_t* pInterface, AQM1602FlagTypeDef_t _displayOnOff, AQM1602FlagTypeDef_t _cursorOnOff, AQM1602FlagTypeDef_t _cursorBlinkOnOff)
{
  uint8_t parameter = (uint8_t)_cursorBlinkOnOff |
                      (uint8_t)_cursorOnOff << 1 |
                      (uint8_t)_displayOnOff << 2;
  AQM1602ResultTypeDef_t result = sendCommand(pInterface, CMD_DISPLAY_ON_OFF, parameter);
  return result;
}
AQM1602ResultTypeDef_t AQM1602_FunctionSet(AQM1602InteraceTypeDef_t* pInterface, AQM1602_DataLengthTypeDef_t _dataLength, AQM1602_LinesTypeDef_t _lines, AQM1602FlagTypeDef_t _doubleHeightOnOff, AQM1602_InstructionTableTypeDef_t _instruction)
{
  AQM1602ResultTypeDef_t result = AQM1602_OK;

  if(_lines == AQM1602_2LINES && _doubleHeightOnOff == AQM1602_ENABLE){
    result = AQM1602_NG;
  }else{
    uint8_t parameter = (uint8_t)_instruction |
                        (uint8_t)_doubleHeightOnOff << 2 |
                        (uint8_t)_lines << 3 |
                        (uint8_t)_dataLength << 4;
    result = sendCommand(pInterface, CMD_FUNCTION_SET, parameter);
  }
  return result;
}
static AQM1602ResultTypeDef_t sendCommand(AQM1602InteraceTypeDef_t* pInterface, uint8_t _command, uint8_t _parameter)
{
  uint8_t dataToSend[] = {CTRL_COMMAND, _command | (_parameter & parameterMask(_command))};

  AQM1602ResultTypeDef_t result = pInterface->i2cWrite(DEVICE_ADDRESS, dataToSend, sizeof(dataToSend));

  return result;
}
AQM1602ResultTypeDef_t AQM1602_SetDDRAMAaddress(AQM1602InteraceTypeDef_t* pInterface, uint8_t _address)
{
  uint8_t parameter = _address;

  AQM1602ResultTypeDef_t result = sendCommand(pInterface, CMD_SET_DDRAM_ADDRESS, parameter);

  return result;
}
AQM1602ResultTypeDef_t AQM1602_SendCharData(AQM1602InteraceTypeDef_t* pInterface, uint8_t* _data, uint8_t _length)
{
  uint8_t lengthToSend = _length;
  if(_length > NUM_OF_CHAR_COLUMN){
    lengthToSend = NUM_OF_CHAR_COLUMN;
  }

  AQM1602ResultTypeDef_t result = sendData(pInterface, _data, (uint16_t)lengthToSend);

  return result;
}
static AQM1602ResultTypeDef_t sendData(AQM1602InteraceTypeDef_t* pInterface, uint8_t* _data, uint16_t _length)
{
  uint16_t lengthToSend = _length;
  if(_length > MAX_DATA_SEND_SIZE){
    lengthToSend = MAX_DATA_SEND_SIZE;
  }

  uint8_t dataToSend[CTRL_BYTE_SIZE + MAX_DATA_SEND_SIZE] = {0};

  dataToSend[0] = (uint8_t)CTRL_DATA;
  memcpy(&dataToSend[1], _data, lengthToSend);

  AQM1602ResultTypeDef_t result = pInterface->i2cWrite(DEVICE_ADDRESS, dataToSend, lengthToSend + CTRL_BYTE_SIZE);

  return result;
}
static uint8_t parameterMask(uint8_t command)
{
  return (command & -command) - 1;
}
AQM1602ResultTypeDef_t AQM1602_SampleInitialize(AQM1602InteraceTypeDef_t* pInterface)
{
  AQM1602ResultTypeDef_t result = AQM1602_OK;

  result = sendCommand(pInterface, 0x38, 0);
  pInterface->delay_ms(MAX_DELAY_AFTER_COMMAND);

  if(result == AQM1602_OK){
    result = sendCommand(pInterface, 0x39, 0);
    pInterface->delay_ms(MAX_DELAY_AFTER_COMMAND);
  }
  if(result == AQM1602_OK){
    result = sendCommand(pInterface, 0x14, 0);
    pInterface->delay_ms(MAX_DELAY_AFTER_COMMAND);
  }
  if(result == AQM1602_OK){
    result = sendCommand(pInterface, 0x7A, 0);
    pInterface->delay_ms(MAX_DELAY_AFTER_COMMAND);
  }
  if(result == AQM1602_OK){
    result = sendCommand(pInterface, 0x54, 0);
    pInterface->delay_ms(MAX_DELAY_AFTER_COMMAND);
  }
  if(result == AQM1602_OK){
    result = sendCommand(pInterface, 0x6C, 0);
    pInterface->delay_ms(MAX_DELAY_AFTER_COMMAND);
  }
  if(result == AQM1602_OK){
    result = sendCommand(pInterface, 0x38, 0);
    pInterface->delay_ms(MAX_DELAY_AFTER_COMMAND);
  }
  if(result == AQM1602_OK){
    result = sendCommand(pInterface, 0x0C, 0);
    pInterface->delay_ms(MAX_DELAY_AFTER_COMMAND);
  }
  if(result == AQM1602_OK){
    result = sendCommand(pInterface, 0x01, 0);
    pInterface->delay_ms(MAX_DELAY_AFTER_COMMAND);
  }

  return result;
}
