#ifndef GAME_H
#define GAME_H

#include "entity.h"

struct game {
  struct entity *player;
  int current_input;
};

void setup_game(struct game *game);
void update_game(struct game *game);
void next_input(struct game *game);
void game_loop(struct game *game);
void close_game(struct game *game);

#endif
