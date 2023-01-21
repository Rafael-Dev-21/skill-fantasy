#include "skfantasy.h"

bool
game_init(void)
{
  initscr();
  cbreak();
  noecho();
  curs_set(0);

  if (!colors_init()) return false;

  level_gen_wild(&level);

  return true;
}

void
game_loop(void)
{
  int input = ' ';

  while (input != 'q')
  {
    level_render(&level);
    input = getch();
  }
}

void
game_exit(void)
{
  endwin();
}
