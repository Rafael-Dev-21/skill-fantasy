#include <ncurses.h>

#include <skfantasy.h>

void initCurses(void)
{
	initscr();
        cbreak();
        noecho();
        curs_set(0);
	timeout(0);
}

void endCurses(void)
{
        endwin();
}
