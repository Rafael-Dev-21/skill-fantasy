#include "skfantasy.h"

int generate_mode(ModeData *data)
{
	clear();
	mvprintw(10, 10, "Generating...");
	refresh();
	if (data->world != NULL) {
		clearArena(data->arena);
	}
  ArenaStatus err;
  if ((err = ArenaNewZ(data->arena, data->world)) != ARENA_OK) {
    endwin();
    char buf[KB(1)];
    ArenaErrStr(buf, KB(1), err, data->arena);
    fprintf(stderr, "generate_mode():%d: initArena() error: %s\n", __LINE__, buf);
    if (err == ARENA_FULL_ERROR) {
      fprintf(stderr, "  Max %zu, asked: %zu\n", ArenaCapacity(data->arena), sizeof(World));
    }
    exit(1);
    return -1;
  }
	init_world(data->world, rand());
	data->player = create_player(data->world);
  if (data->player == NULL) {
    return -1;
  }

	for (int i = 0; i < 8; i++) {
		(void)create_fungi(data->world);
	}

  for (int i = 0; i < 24; i++) {
    (void)create_bat(data->world);
  }

	mvprintw(11, 10, "[Press any key]");
	refresh();

	(void)getch();
	return 2;
}
