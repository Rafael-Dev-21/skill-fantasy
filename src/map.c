#include <noise.h>
#include <colors.h>
#include <map.h>
#include <math.h>

enum tile_type get_tile(float elevation)
{
	if (elevation < .1)
		return TILE_WATER;
	else if (elevation < .2)
		return TILE_SAND;
	else if (elevation < .5)
		return TILE_GRASS;
	else
		return TILE_MOUNTAIN;
}

struct tile **create_map(void)
{
	struct tile **tiles = calloc(MAP_HEIGHT, sizeof(*tiles));

	for (int i = 0; i < MAP_HEIGHT; i++) {
		tiles[i] = calloc(MAP_WIDTH, sizeof(**tiles));
	}

	return tiles;
}

struct position setup_map(struct tile **tiles)
{
	struct position start_pos = { 0, 0 };

	int player = 0;

	for (int y = 0; y < MAP_HEIGHT; y++)
	for (int x = 0; x < MAP_WIDTH; x++) {
		float nx = x / 32.0 - 0.5;
		float ny = y / 32.0 - 0.5;

		float e = pow(fbm(nx, ny, 1, 3) * 1.2, 2.75);

		enum tile_type type = get_tile(e);

		if (type == TILE_GRASS && player == 0) {
			start_pos.y = y;
			start_pos.x = x;
			player = 1;
		}

		tiles[y][x].walkable = true;
		switch (type) {
		case TILE_GRASS:
			tiles[y][x].ch = ',';
			tiles[y][x].color = SKPAIR_GRASS;
			break;
		case TILE_SAND:
			tiles[y][x].ch = '~';
			tiles[y][x].color = SKPAIR_SAND;
			break;
		case TILE_WATER:
			tiles[y][x].ch = '~';
			tiles[y][x].color = SKPAIR_WATER;
			break;
		case TILE_MOUNTAIN:
			tiles[y][x].ch = '^';
			tiles[y][x].color = SKPAIR_MOUNTAIN;
			tiles[y][x].walkable = false;
			break;
		}
	}

	return start_pos;
}

void free_map(struct tile **tiles)
{
	for (int i = 0; i < MAP_HEIGHT; i++) {
		free(tiles[i]);
	}
	free(tiles);
}
