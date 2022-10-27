#ifndef GAME_H
#define GAME_H

#include "entity.h"

typedef Game *GamePtr;

typedef struct {
  EntityPtr player;
  int prevInput;
} Game;

void setupGame(GamePtr game);
void updateGame(GamePtr game);
void nextInput(GamePtr game);
void gameLoop(GamePtr game);
void freeGame(GamePtr game);

#endif
