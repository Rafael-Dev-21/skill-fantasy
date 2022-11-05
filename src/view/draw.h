#ifndef SKDRAW_H
#define SKDRAW_H

#include "../game/game.h"

namespace view {
namespace draw {
void setup();

void draw_map(Game *g);

void close();
};  // namespace draw

};  // namespace view

#endif
