#include "skfantasy.h"

int start_mode(ModeData *data)
{
	clear();

	mvprintw(1, 1, "SKILL FANTASY %s", data->version);

	mvprintw(4, 10, "(s)tart");
	mvprintw(5, 10, "ESC for quit");
	
	refresh();

	switch (getch()) {
	case 's':
		return 1;
	case ESC:
		return -1;
	default:
		return 0;
	}
}
