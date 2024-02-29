#include <stdlib.h>

#ifdef __linux__
#include <ncurses/ncurses.h>
#else
#include <curses.h>
#endif

#include "engine.h"
#include "move.h"
#include "world.h"
#include "draw.h"

#define MAP_WIDTH 1024
#define MAP_HEIGHT 1024

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
	Point ppos = { 10, 10 }; // posição do jogador
	Direction pdir = UP; // direção do jogador
	
	Map * map = create_map(MAP_WIDTH, MAP_HEIGHT); // mapa

	init_map(map);

	init_curses();

	int ch = 0; // input
	do {
		clear();


		Direction old_dir = pdir;

		pdir = dir_from_ch(ch, pdir);

		if (ch == 'h' 
			|| ch == 'j'
			|| ch == 'k'
			|| ch == 'l') {
			if (pdir == old_dir)
				move_and_collide(map, &ppos, pdir);
		}

		Point cell = ppos;
		move_from(&cell, pdir);

		if (ch == 'p') {
			place_wall(map, cell);
		}

		if (ch == 'b') {
			break_wall(map, cell);
		}

		draw_map(map, ppos);
		draw_player(ppos, cell);
	} while((ch = getch()) != ESC);

	endwin();

	free_map(map);

	return EXIT_SUCCESS;
}

