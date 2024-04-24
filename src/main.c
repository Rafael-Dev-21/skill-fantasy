#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <ncursesw/ncurses.h>
#else
#include <curses.h>
#endif

#include "engine.h"
#include "modes.h"

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

#if defined(_WIN32) || defined(__MINGW__)
	fopen_s(&file_version, "version.txt", "r");
#else
	file_version = fopen("version.txt", "r");
#endif

	fgets(data.version, 256, file_version);
	
	fclose(file_version);

	data.version[strlen(data.version)-1] = '\0';
	
	Mode *mode = &(Mode){&start_mode};

	init_curses();

	while (mode != NULL) {
		mode = mode->next(&data);
	}

	endwin();

	return EXIT_SUCCESS;
}

