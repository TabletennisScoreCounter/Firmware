#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

typedef enum {
  PLAYERCOLOR_RED = 0,
  PLAYERCOLOR_BLUE,
  PLAYERCOLOR_GREEN,
  PLAYERCOLOR_YELLOW
} PlayerColor_t;

PlayerColor_t GetCurrentServerColor();
PlayerColor_t GetCurrentReceiverColor();

void GameManagingTask(const void* args);

#endif
