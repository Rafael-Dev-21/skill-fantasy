#include "skfantasy.h"

#include <curses.h>

void curses_init(void)
{
  initscr();
  raw();
  noecho();
  curs_set(false);

  if (has_colors()) {  
	  start_color();  

  	for (int i = 0; i < 16; i += 1) {  
	  	init_pair(i+1, i, 0);  
  	}  
  }
}

void curses_cleanup(void)
{
  endwin();
  curs_set(true);
}
