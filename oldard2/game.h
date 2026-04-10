#pragma once

#include "entity.h"
#include "level.h"

typedef struct {
    Level level;
    World world;
} Game;

bool gameInit(Game *game);
void gameLoop(Game *game);
void gameClose(Game *game);

