#ifndef COLORS_H
#define COLORS_H

#include "view.h"

namespace view {
namespace colors {
enum {
  SKPAIR_GRASS = 1,
  SKPAIR_SAND,
  SKPAIR_WATER,
  SKPAIR_MOUNTAIN,
  SKPAIR_PLAYER,
  SKPAIR_COUNT
};

bool setup();

};  // namespace colors

};  // namespace view

#endif
