#include "skfantasy.h"

Mode *generate_mode(ModeData *data)
{
	clear();
	mvprintw(10, 10, "Generating...");
	refresh();
	if (data->world != NULL) {
		free_world(data->world);
	}
	data->world = create_world(1024, 1024);
	init_world(data->world);
	if (data->player != NULL) {
		free_creature(data->player);
	}
	data->player = create_player(data->world);

	for (int i = 0; i < 256; i++) {
		create_fungi(data->world);
	}

	mvprintw(11, 10, "[Press any key]");
	refresh();

	getch();
	return &(Mode){&play_mode};
}
