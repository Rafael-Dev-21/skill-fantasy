#ifndef SKDRAW_H
#define SKDRAW_H

#include "entity.h"
#include "map.h"
#include "game.h"

void draw_setup(void);

void draw_entity(struct entity *entity, int offy, int offx);

void draw_entity_on(struct entity *entity, int y, int x);

void draw_map(struct tile **map, struct position player);

void draw_game(struct game *game);

void draw_close(void);

#endif
