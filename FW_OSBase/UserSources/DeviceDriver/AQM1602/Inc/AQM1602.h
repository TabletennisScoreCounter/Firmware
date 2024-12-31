#ifndef AQM1602_H_
#define AQM1602_H_

#include <stdint.h>

typedef enum AQM1602ResultTypeDef{
  AQM1602_OK = 0,
  AQM1602_NG
}AQM1602ResultTypeDef_t;
typedef enum AQM1602FlagTypeDef{
  AQM1602_DISABLE = 0,
  AQM1602_ENABLE = 1
}AQM1602FlagTypeDef_t;
typedef enum AQM1602_CursorDirectionTypeDef{
  AQM1602_DECREMENT = 0,
  AQM1602_INCREMENT = 1
}AQM1602_CursorDirectionTypeDef_t;
typedef enum AQM1602_DataLengthTypeDef{
  AQM1602_4BIT = 0,
  AQM1602_8BIT = 1
}AQM1602_DataLengthTypeDef_t;
typedef enum AQM1602_LinesTypeDef{
  AQM1602_1LINE = 0,
  AQM1602_2LINES = 1
}AQM1602_LinesTypeDef_t;
typedef enum AQM1602_InstructionTableTypeDef{
  AQM1602_NORMALINSTRUCTION = 0,
  AQM1602_EXTENSIONINSTRUCTION = 1
}AQM1602_InstructionTableTypeDef_t;
typedef enum AQM1602_BiasSelectionTypeDef{
  AQM1602_BIAS_1_4 = 1,
  AQM1602_BIAS_1_5 = 0,
}AQM1602_BiasSelectionTypeDef_t;
typedef enum AQM1602_InternalOSCFrequencyTypeDef{
  AQM1602_IFREQ_120 = 0,
  AQM1602_IFREQ_133 = 1,
  AQM1602_IFREQ_149 = 2,
  AQM1602_IFREQ_167 = 3,
  AQM1602_IFREQ_192 = 4,
  AQM1602_IFREQ_227 = 5,
  AQM1602_IFREQ_277 = 6,
  AQM1602_IFREQ_347 = 7
}AQM1602_InternalOSCFrequencyTypeDef_t;
enum AQM1602_DDRAddress{
  AQM1602_DDRADDR_LEFTEND_LINE1 = 0x00,
  AQM1602_DDRADDR_RIGHTEND_LINE1 = 0x0F,
  AQM1602_DDRADDR_LEFTEND_LINE2 = 0x40,
  AQM1602_DDRADDR_RIGHTEND_LINE2 = 0x4F
};



typedef struct AQM1602InteraceTypeDef{
  AQM1602ResultTypeDef_t (*i2cWrite)(uint8_t _slaveAddress, const uint8_t* _data, uint16_t _length);
  void (*delay_ms)(uint32_t milisecond);
}AQM1602InteraceTypeDef_t;

AQM1602ResultTypeDef_t AQM1602_WaitForBoot(AQM1602InteraceTypeDef_t* pInterface);
AQM1602ResultTypeDef_t AQM1602_ClearDisplay(AQM1602InteraceTypeDef_t* pInterface);
AQM1602ResultTypeDef_t AQM1602_ReturnHome(AQM1602InteraceTypeDef_t* pInterface);
AQM1602ResultTypeDef_t AQM1602_EntryModeSet(AQM1602InteraceTypeDef_t* pInterface, AQM1602_CursorDirectionTypeDef_t _cursorDirection, AQM1602FlagTypeDef_t _displayShift);
AQM1602ResultTypeDef_t AQM1602_DisplayOnOff(AQM1602InteraceTypeDef_t* pInterface, AQM1602FlagTypeDef_t _displayOnOff, AQM1602FlagTypeDef_t _cursorOnOff, AQM1602FlagTypeDef_t _cursorBlinkOnOff);
AQM1602ResultTypeDef_t AQM1602_FunctionSet(AQM1602InteraceTypeDef_t* pInterface, AQM1602_DataLengthTypeDef_t _dataLength, AQM1602_LinesTypeDef_t _lines, AQM1602FlagTypeDef_t _doubleHeightOnOff, AQM1602_InstructionTableTypeDef_t _instruction);
AQM1602ResultTypeDef_t AQM1602_SetDDRAMAaddress(AQM1602InteraceTypeDef_t* pInterface, uint8_t _address);
AQM1602ResultTypeDef_t AQM1602_SendCharData(AQM1602InteraceTypeDef_t* pInterface, uint8_t* _data, uint8_t _length);
AQM1602ResultTypeDef_t AQM1602_SetInternalOSCFrequency(AQM1602InteraceTypeDef_t* pInterface, AQM1602_BiasSelectionTypeDef_t _bias, AQM1602_InternalOSCFrequencyTypeDef_t _ifreq);
/**
 * @brief データシートに記載のサンプル初期化コード
 *
 * @param pInterface インターフェース構造体
 *
 * @return 通信成功 : AQM1602_OK, 失敗 : AQM1602_NG
 */
AQM1602ResultTypeDef_t AQM1602_SampleInitialize(AQM1602InteraceTypeDef_t* pInterface);
#endif
