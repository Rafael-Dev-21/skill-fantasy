#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

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

#if defined(_WIN32) || defined(__MINGW__)
	fopen_s(&file_version, "version.txt", "r");
#else
	file_version = fopen("version.txt", "r");
#endif

	fgets(data.version, 256, file_version);

	fclose(file_version);

	int mode = 0;

	init_curses();

	lua_State *L;

	L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, "data/main.lua");

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

	lua_close(L);
	endwin();

	return EXIT_SUCCESS;
}

