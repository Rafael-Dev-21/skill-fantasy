#include "skfantasy.h"
#include <curses.h>

void draw_start_menu(void)
{
  char *title = "Skill Fantasy v0.4.0";
  move(1, (COLS-strlen(title))/2);
  printw("%s", title);

  const char *options[] = {  
    "<s>  to Start Game",  
    "<C-q> to Quit Game"  
  };  

  const int Y = 3;  
  const int X = 3;  
  for (int i = 0; i < 2; i++) {  
    move(Y+i, X);  
    printw("%s", options[i]);  
  }
}

void draw_mob(mob_t *mob, position_t center)
{
  int mx = mob->pos.x - center.x;
  int my = mob->pos.y - center.y;
  if (mx < 0 || mx >= COLS || my < 0 || my >= LINES-3) {
    return;
  }
  move(my, mx * 2);
  mvaddch(my, mx, mob->glyph);
}

void draw_map(map_t map, position_t center)
{
  for (int i = 0; i < LINES-3; i++) {
    for (int j = 0; j < COLS/2; j++) {
      int mapx = j + center.x+COLS/4;
      int mapy = i + center.y;
      move(i, j*2);
      if (mapx < 0 || mapy < 0 || mapx >= MAP_WIDTH || mapy >= MAP_HEIGHT || map[mapy][mapx].visible == false) {
        addch(' ');
      } else {
        addch(map[mapy][mapx].glyph);
      }
    }
  }
}
