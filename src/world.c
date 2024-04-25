#include <stdlib.h>

#include "skfantasy.h"
#include "noise.h"

World * create_world(int width, int height)
{
	World * result = (World *)calloc(1, sizeof(World));
	if (result == NULL) {
		return NULL;
	}

	result->width = width;
	result->height = height;
	result->tiles = (Tile * *)calloc(result->height, sizeof(Tile *));
	if (result->tiles == NULL) {
		free(result);
		return NULL;
	}
	for (int i = 0; i < result->height; i++) {
		result->tiles[i] = (Tile *)calloc(result->width, sizeof(Tile));
	}

	result->creatures = NULL;

	return result;
}

void free_world(World * world)
{
	if (world == NULL) {
		return;
	}
	for (int i = 0; i < world->height; i++) {
		free(world->tiles[i]);
	}
	free(world->tiles);

	Creature *it = world->creatures;
	while (it != NULL) {
		Creature *c = it;
		it = it->next;
		free_creature(c);
	}

	free(world);
	world = NULL;
}

void init_world(World * world)
{
	if (world == NULL) {
		return;
	}

	FBMParams params = default_fbm;
	params.noisefn = simplex2d;
	params.amplitude = 0.5;
	params.octaves = 3;

	for (int j = 0; j < world->height; j += 1) {
		for (int i = 0; i < world->width; i += 1) {
			Tile *tile = tile_at(world, (Point){i, j});
			if (tile == NULL) {
				return;
			}
			tile->type = TILE_STONE;
			tile->object = fbm2d(i/16.0 - 0.5, j/16.0 - 0.5, params) <= 0.5 ? OBJ_NONE : OBJ_WALL;
		}
	}
}

Tile *tile_at(World * world, Point cell)
{
	if (world == NULL) {
		return NULL;
	}
	if (cell.x < 0) {
		return NULL;
	}
	if (cell.y < 0) {
		return NULL;
	}
	if (cell.x >= world->width) {
		return NULL;
	}
	if (cell.y >= world->height) {
		return NULL;
	}
	return &world->tiles[cell.y][cell.x];
}

Creature *creature_at(World *world, Point cell)
{
	Creature *it = world->creatures;
	while (it != NULL) {
		if (it->position.x == cell.x &&
			it->position.y == cell.y) {
			return it;
		}
		it = it->next;
	}
	return NULL;
}

void place_wall(World * world, Point cell)
{
	if (world == NULL) return;
	if (cell.x < 0) return;
	if (cell.x >= world->width) return;
	if (cell.y < 0) return;
	if (cell.y >= world->height) return;
	tile_at(world, cell)->object = OBJ_WALL;
}

void break_wall(World * world, Point cell)
{
	if (world == NULL) return;
	if (cell.x < 0) return;
	if (cell.x >= world->width) return;
	if (cell.y < 0) return;
	if (cell.y >= world->height) return;
	tile_at(world, cell)->object = OBJ_NONE;

}

bool is_solid(Tile * tile)
{
	if (tile == NULL) {
		return false;
	}
	return obj_types[tile->object].solid;
}

void add_creature_rand_empty(World *world, Creature *creature)
{
	if (world == NULL) {
		return;
	}
	if (creature == NULL) {
		return;
	}

	Point cell;
	
	do {
		cell.x = rand() % world->width;
		cell.y = rand() % world->height;
	} while (is_solid(tile_at(world, cell)) || creature_at(world, cell));

	creature->position = cell;

	creature->next = world->creatures;
	world->creatures = creature;
}

void world_remove(World *world, Creature *creature)
{
	Creature *it = world->creatures;
	if (creature == it) {
		world->creatures = it->next;
	} else {
		Creature *last = it;
		it = it->next;
		while (it != NULL) {
			if (creature == it) {
				last->next = it->next;
				return;
			}
			last = it;
			it = it->next;
		}
	}
}
