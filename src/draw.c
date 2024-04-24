#ifdef __linux__
#include <ncursesw/ncurses.h>
#else
#include <curses.h>
#endif

#include "position.h"
#include "map.h"
#include "creature.h"
#include "draw.h"

void draw_map(Map * const map, Point center)
{
	int startx = center.x - COLS/2;
	int starty = center.y - LINES/2;

	for (int row = 0; row < LINES; row += 1) {
		for (int col = 0; col < COLS; col += 1) {
			int mapx = startx + col;
			int mapy = starty + row;
			if (mapx < 0 || mapy < 0
				|| mapx >= map->width || mapy >= map->height) {
				mvaddch(row, col, ' ');
				continue;
			}

			int sprite = ' ';
			Tile tile = map->tiles[mapy][mapx];
			TileType tile_type = tile_types[tile.type];
			ObjectType obj_type = obj_types[tile.object];

			if (obj_type.glyph != -1)
				sprite = obj_type.glyph | COLOR_PAIR(obj_type.color);
			else
				sprite = tile_type.glyph | COLOR_PAIR(tile_type.color);

			mvaddch(row, col, sprite);
		}
	}
}

void draw_creature(Creature *creature, Point player)
{
	Point center = { COLS / 2, LINES / 2 };
	Point cursor = {0,0};

	if (creature == NULL) {
		return;
	}
	
	Point pos = creature->position;

	switch(creature->facing) {
	case UP:
		cursor.y = -1;
		break;
	case DOWN:
		cursor.y = 1;
		break;
	case LEFT:
		cursor.x = -1;
		break;
	case RIGHT:
		cursor.x = 1;
		break;
	default:
		cursor = (Point){0, 0};
	}

	Point modified_pos = { center.x + pos.x - player.x, center.y + pos.y - player.y }; 

	Point cell = { cursor.x + modified_pos.x, cursor.y + modified_pos.y };
	mvaddch(cell.y, cell.x, 'x');
	mvaddch(modified_pos.y, modified_pos.x, creature->glyph | COLOR_PAIR(creature->color));
}
