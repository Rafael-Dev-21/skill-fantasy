#ifdef _MSC_VER
# define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#include "skfantasy.h"

TileType tile_types[TILE_COUNT] = {
	{ ' ', 1 },
	{ ',', 3 },
	{ '~', 4 },
	{ '7', 5 },
	{ '.', 9 },
};

ObjectType obj_types[OBJ_COUNT] = {
	{ -1, 0, false },
	{ '#', 8, true },
};

int main(int argc, char *argv[])
{
	ModeData data = {NULL, NULL, {0}};

	FILE *file_version;
	file_version = fopen("version.txt", "r");
	fgets(data.version, 256, file_version);
	fclose(file_version);

	int mode = 0;

	init_curses();
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

