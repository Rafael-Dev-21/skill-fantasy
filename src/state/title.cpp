#include <curses.h>

#include "engine.hpp"

static void printTitle() {
  int startx = COLS / 2 - 8;

  clear();
  mvaddstr(2, startx, "#== # # =#= #   #  ");
  mvaddstr(3, startx, "#=# ##   #  #   #  ");
  mvaddstr(4, startx, "==# # # =#= #== #==");
  mvaddstr(5, startx, "@====>FANTASY<====@");
  mvaddstr(6, startx, "v0.1.0");

  mvaddstr(8, startx, "(s)start, (q)uit");
  refresh();
}

EngineState titleAction() {
  printTitle();

  switch (getch()) {
    case 'q':
      return ENGINE_EXIT;
    case 's':
      return ENGINE_GEN;
    default:
      return ENGINE_TITLE;
  }
};