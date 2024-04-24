#include <stdlib.h>

#include "position.h"
#include "map.h"
#include "noise.h"

Map * create_map(int width, int height)
{
	Map * result = (Map *)calloc(1, sizeof(Map));

	result->width = width;
	result->height = height;
	result->tiles = (Tile * *)calloc(result->height, sizeof(Tile *));
	for (int i = 0; i < result->height; i++) {
		result->tiles[i] = (Tile *)calloc(result->width, sizeof(Tile));
	}

	return result;
}

void free_map(Map * map)
{
	for (int i = 0; i < map->height; i++) {
		free(map->tiles[i]);
	}
	free(map->tiles);
	free(map);
	map = NULL;
}

void init_map(Map * map)
{
	FBMParams params = default_fbm;
	params.noisefn = simplex2d;
	params.amplitude = 0.5;
	params.octaves = 3;

	for (int j = 0; j < map->height; j += 1) {
		for (int i = 0; i < map->width; i += 1) {
			Tile *tile = &map->tiles[j][i];
			tile->type = TILE_STONE;
			tile->object = fbm2d(i/16.0 - 0.5, j/16.0 - 0.5, params) <= 0.5 ? OBJ_NONE : OBJ_WALL;
		}
	}
}

void place_wall(Map * map, Point cell)
{
	if (cell.x < 0) return;
	if (cell.x >= map->width) return;
	if (cell.y < 0) return;
	if (cell.y >= map->height) return;
	map->tiles[cell.y][cell.x].object = OBJ_WALL;
}

void break_wall(Map * map, Point cell)
{
	if (cell.x < 0) return;
	if (cell.x >= map->width) return;
	if (cell.y < 0) return;
	if (cell.y >= map->height) return;
	map->tiles[cell.y][cell.x].object = OBJ_NONE;

}

bool is_solid(Map * const map, Point cell)
{
	if (cell.x < 0) return true;
	if (cell.x >= map->width) return true;
	if (cell.y < 0) return true;
	if (cell.y >= map->height) return true;

	return obj_types[map->tiles[cell.y][cell.x].object].solid;
}
