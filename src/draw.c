#include <common.h>
#include <draw.h>

void draw_setup(void)
{
	initscr();
	noecho();
	curs_set(0);
}

void draw_entity(struct entity *entity, int offy, int offx)
{
	mvaddch(entity->pos.y + offy, entity->pos.x + offx, entity->ch | COLOR_PAIR(entity->color));
}

void draw_entity_on(struct entity *entity, int y, int x)
{
	mvaddch(y, x, entity->ch | COLOR_PAIR(entity->color));
}

void draw_map(struct tile **map, struct position player)
{
	int center_y = LINES / 2;
	int center_x = COLS / 2;

	int row = 0;
	for (int y = -center_y; y < center_y; y++) {
		int col = 0;
		for (int x = -center_x; x < center_x; x++) {
			int map_y = y + player.y;
			int map_x = x + player.x;

			if (map_y >= 0 && map_x >= 0 && map_y < MAP_HEIGHT && map_x < MAP_WIDTH)
				mvaddch(row, col, map[map_y][map_x].ch | COLOR_PAIR(map[map_y][map_x].color));
			else
				mvaddch(row, col, ' ');

			col++;
		}
		row++;
	}
}

void draw_game(struct game *game)
{
	clear();
	draw_map(game->map, game->player->pos);
	draw_entity_on(game->player, LINES / 2, COLS / 2);
	refresh();
}

void draw_close(void)
{
	endwin();
}
