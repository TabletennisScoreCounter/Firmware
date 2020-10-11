#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <stdint.h>
#include "FullColorLEDDriver.h"

typedef enum {
  PLAYERCOLOR_RED = LEDCOLOR_RED,
  PLAYERCOLOR_BLUE = LEDCOLOR_BLUE,
  PLAYERCOLOR_GREEN = LEDCOLOR_GREEN,
  PLAYERCOLOR_YELLOW = LEDCOLOR_YELLOW
} PlayerColor_t;

typedef enum {
  PLAYSIDE_LEFT = 0,
  PLAYSIDE_RIGHT
} PlaySide_t;

PlayerColor_t GetCurrentServerColor();
PlayerColor_t GetCurrentReceiverColor();
uint32_t GetScoreCount(PlaySide_t playSide);
uint32_t GetGameCount(PlaySide_t playSide);
void GameManagingTask(const void* args);

#endif
