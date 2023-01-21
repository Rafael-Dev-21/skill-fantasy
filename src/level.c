#include "skfantasy.h"

struct tile
{
  char sprite;
  int appaerance;
} const tileset[] = { { ',', COLOR_PAIR(PAIR_GRASS) }, { '~', COLOR_PAIR(PAIR_MUD) | A_DIM } };

void level_gen_wild(struct level *level)
{
  for (int row = 0; row < MAP_SIZE; ++row)
  {
    for (int col = 0; col < MAP_SIZE; ++col)
    {
      if (((row % 2) == 0) && ((col % 2) == 0))
      {
        level->visual[row][col] = 1;
        level->logic[row][col] = true;
      }
      else
      {
        level->visual[row][col] = 0;
        level->logic[row][col] = false;
      }
    }
  }
}

void
level_render(struct level *level)
{
  for (int row = 0; row < MAP_SIZE; ++row)
  {
      for (int col = 0; col < MAP_SIZE; ++col)
      {
        struct tile tile = tileset[level->visual[row][col]];

        mvaddch (row, col, tile.sprite | tile.appaerance);
      }
   }
}
