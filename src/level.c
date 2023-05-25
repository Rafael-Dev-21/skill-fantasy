#include <stdlib.h>
#include <strings.h>

#include <ncurses.h>

#include <skfantasy.h>

level_t *newLevel(position_t pos, int width, int height)
{
	unsigned len = width * height;
	level_t *level = (level_t *) malloc(sizeof(level_t) + sizeof(tile_t) * len);

	level->pos = pos;
	level->width = width;
	level->height = height;
	level->length = len;
	
	memset(level->tiles, TILE_GRASS, level->length);

	return level;
}

void drawLevel(level_t *level)
{
	for (int i = 0; i < level->length; i++) {
		int y = level->pos.y + i / level->width;
		int x = level->pos.x + i % level->width;

		int sprite = ' ';

		switch (level->tiles[i]) {
		case TILE_GRASS:
			sprite = ',';
		}

		if (sprite != ' ')
			mvaddch(y, x, sprite);
		else
			mvprintw(y, x, "%d", level->tiles[i]);
	}
}

void freeLevel(level_t *level)
{
	free(level);
}
