#ifdef _MSC_VER
# define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#include "arena.h"
#include "skfantasy.h"
#ifdef USE_GUILE
#include "api/guile_api.h"
#endif

TileType tile_types[TILE_COUNT] = {
	{ ' ', 1, {}, {} },
	{ ',', 3 , {}, {} },
	{ '~', 4, {}, {} },
	{ '7', 5, {}, {} },
	{ '.', 9, {}, {} },
  { '3', 4, {}, {true, 1, TILE_MUD} },
  { '3', 2, {true, 0, TILE_SOIL}, {} },
};

ObjectType obj_types[OBJ_COUNT] = {
	{ -1, 0, false, false, {} },
	{ '#', 8, true, true, {} },
  { '*', 2, false, true, {} },
  { ',', 12, true, true, { true, 32, OBJ_WHEAT } },
  { '1', 12, true, true, {} },
};

uint8_t abuf[MB(32)] = {0};

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  Arena arena;
  ArenaStatus err;
  if ((err = initArena(&arena, abuf, MB(32))) != ARENA_OK) {
    char buf[KB(1)];
    ArenaErrStr(buf, KB(1), err, &arena);
    fprintf(stderr, "main():%d: initArena() error: %s\n", __LINE__, buf);
    return 1;
  }

#ifndef VERSION
	ModeData data = {&arena, NULL, NULL, {0}};

	FILE *file_version;
	file_version = fopen("version.txt", "r");
	if (file_version)
    fgets(data.version, 256, file_version);
  else
    snprintf(data.version, 256, "version unknown");
	fclose(file_version);
#else
  ModeData data = {&arena, NULL, NULL, VERSION};
#endif

	int mode = 0;
  time_t seed = time(NULL);
  srand(*(int*)&seed);
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

