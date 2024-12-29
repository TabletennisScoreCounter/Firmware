#ifndef FULLCOLORLEDDRIVER_H_
#define FULLCOLORLEDDRIVER_H_

typedef enum {
  LEDCOLOR_BLUE = 0,
  LEDCOLOR_RED,
  LEDCOLOR_GREEN,
  LEDCOLOR_YELLOW
}LEDColor_t;

void EnableFullColorLED();
void SetServerLEDColor(LEDColor_t ledColor);
void SetReceiverLEDColor(LEDColor_t ledColor);

#endif
