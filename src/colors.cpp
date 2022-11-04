#include "colors.h"

bool setup_colors(void) {
  if (!has_colors())
    return false;

  start_color();

  init_pair(SKPAIR_GRASS, COLOR_YELLOW, COLOR_GREEN);
  init_pair(SKPAIR_SAND, COLOR_YELLOW, COLOR_WHITE);
  init_pair(SKPAIR_WATER, COLOR_CYAN, COLOR_BLUE);
  init_pair(SKPAIR_MOUNTAIN, COLOR_BLACK, COLOR_WHITE);
  init_pair(SKPAIR_PLAYER, COLOR_RED, COLOR_MAGENTA);

  return true;
}
