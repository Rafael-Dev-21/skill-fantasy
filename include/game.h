#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include "map.h"

struct game {
  struct entity *player;
  struct tile **map;
  int current_input;
};

void setup_game(struct game *game);
void update_game(struct game *game);
void next_input(struct game *game);
void game_loop(struct game *game);
void close_game(struct game *game);

#endif
