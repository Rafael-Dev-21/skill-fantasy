#ifdef __linux__
#include <ncurses/ncurses.h>
#else
#include <curses.h>
#endif

#include "engine.h"

void init_curses(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	if (has_colors()) {
		start_color();

		for (int i = 0; i < 16; i += 1) {
			init_pair(i+1, i, 0);
		}
	}
}
