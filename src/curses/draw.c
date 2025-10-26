#include "skfantasy.h"


void draw_creature(Creature const * const creature, Point player)
{
	Point center = { COLS / 2, LINES / 2 };
	Point cursor = {0,0};

	if (creature == NULL) {
		return;
	}
	
	Point pos = creature->position;
	cursor = point_from_dir(creature->facing);

	Point modified_pos = { center.x + pos.x - player.x, center.y + pos.y - player.y }; 

	Point cell = { cursor.x + modified_pos.x, cursor.y + modified_pos.y };
	mvaddch(cell.y, cell.x, 'x');
	mvaddch(modified_pos.y, modified_pos.x, creature->glyph | COLOR_PAIR(creature->color));
}

void draw_world(World const * const world, Point center)
{
	if (world == NULL) {
		return;
	}

	int startx = center.x - COLS/2;
	int starty = center.y - LINES/2;

	for (int row = 0; row < LINES; row += 1) {
		for (int col = 0; col < COLS; col += 1) {
			int mapx = startx + col;
			int mapy = starty + row;
			if (mapx < 0 || mapy < 0
				|| mapx >= world->width || mapy >= world->height) {
				mvaddch(row, col, ' ');
				continue;
			}

			int sprite = ' ';
			Tile tile = world->tiles[mapy * world->width + mapx];
			TileType tile_type = tile_types[tile.type];
			ObjectType obj_type = obj_types[tile.object];

			if (obj_type.glyph != -1)
				sprite = obj_type.glyph | COLOR_PAIR(obj_type.color);
			else
				sprite = tile_type.glyph | COLOR_PAIR(tile_type.color);

			mvaddch(row, col, sprite);
		}
	}

	Creature *it = world->creatures;

	while (it != NULL) {
		draw_creature(it, center);
		it = it->next;
	}
}

