#ifndef SKDRAW_H
#define SKDRAW_H

#include "entity.h"
#include "game.h"
#include "map.h"

namespace draw {
void setup();

void draw_map(Game *g);

void close();

}; // namespace draw

#endif
