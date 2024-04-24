#ifdef __linux__
#include <ncursesw/ncurses.h>
#else
#include <curses.h>
#endif

#include "modes.h"
#include "factories.h"

Mode *generate_mode(ModeData *data)
{
	clear();
	mvprintw(10, 10, "Generating...");
	refresh();
	if (data->map != NULL) {
		free_map(data->map);
	}
	data->map = create_map(1024, 1024);
	init_map(data->map);
	if (data->player != NULL) {
		free_creature(data->player);
	}
	data->player = create_player(data->map);

	mvprintw(11, 10, "[Press any key]");
	refresh();

	getch();
	return &(Mode){&play_mode};
}
