#ifdef _MSC_VER
# define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#include "skfantasy.h"
#ifdef USE_GUILE
#include "api/guile_api.h"
#endif

TileType tile_types[TILE_COUNT] = {
	{ ' ', 1 },
	{ ',', 3 },
	{ '~', 4 },
	{ '7', 5 },
	{ '.', 9 },
};

ObjectType obj_types[OBJ_COUNT] = {
	{ -1, 0, false, false },
	{ '#', 8, true, true },
};

int main(int argc, char *argv[])
{
#ifndef VERSION
	ModeData data = {NULL, NULL, {0}};

	FILE *file_version;
	file_version = fopen("version.txt", "r");
	fgets(data.version, 256, file_version);
	fclose(file_version);
#else
  ModeData data = {NULL, NULL, VERSION};
#endif

	int mode = 0;

	init_curses();
#ifdef USE_GUILE
  skfantasy_api_guile_init();
#endif
	while (mode != -1) {
		switch (mode) {
		case 0:
			mode = start_mode(&data);
			break;
		case 1:
			mode = generate_mode(&data);
			break;
		case 2:
			mode = play_mode(&data);
			break;
		}
	}
	endwin();

	return EXIT_SUCCESS;
}

