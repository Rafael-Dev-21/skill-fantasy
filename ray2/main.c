#include "skfantasy.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <curses.h>

double hash(double x, double y)
{
  const size_t w = 8 * sizeof(unsigned);
  const size_t s = w/2;

  uint32_t a = x, b = y;  
  a *= 3284157443;  
  b ^= a << s | a >> (w - s);  
  b *= 1911520717;  
  a ^= b << s | b >> (w - s);  
  a *= 2048419325;  
  return a/(double)UINT32_MAX;
}

int main(void)
{
  mob_t player = {.glyph='@'};
  map_t map = {0};
  int screen = 0, input = 0;

  srand(50);  

  curses_init();  

  draw_start_menu();  
  while ((input=getch()) != CTRL_KEY('q')) {  
    clear();  
    if (screen == 0) {  
      screen = game_start(&player, map, input);  
      if (screen == 1) {  
        clear();  
        game_play(&player, map, 0);  
      }  
    } else if (screen == 1) {  
      screen = game_play(&player, map, input);  
      if (screen == 0) {  
        clear();  
        game_start(&player, map, 0);  
      }  
    }  
    refresh();  
  }  
  curses_cleanup();  
  return(0);
}

#include "noise/math.c"
#include "noise/noise.c"

#include "curses.c"
#include "engine.c"
#include "mob.c"
#include "map.c"
#include "draw.c"
