#include "skfantasy.h"

Mode *start_mode(ModeData *data)
{
	clear();

	mvprintw(1, 1, "SKILL FANTASY %s", data->version);

	mvprintw(4, 10, "(s)tart");
	mvprintw(5, 10, "ESC for quit");
	
	refresh();

	switch (getch()) {
	case 's':
		return &(Mode){&generate_mode};
	case ESC:
		return NULL;
	default:
		return &(Mode){&start_mode};
	}
}
