#ifndef GAME_H
#define GAME_H

#include "entity.h"

typedef struct {
  EntityPtr player;
  int curInput;
} Game;

typedef Game *GamePtr;

void setupGame(GamePtr game);
void updateGame(GamePtr game);
void nextInput(GamePtr game);
void GameLoop(GamePtr game);
void CloseGame(GamePtr game);

#endif
