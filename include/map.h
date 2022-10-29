#ifndef MAP_H
#define MAP_H

#include "common.h"
#include "position.h"

#define MAP_WIDTH 128
#define MAP_HEIGHT 128

enum tile_type {
	TILE_GRASS,
	TILE_SAND,
	TILE_WATER,
	TILE_MOUNTAIN
};

struct tile {
	char ch;
	int color;
	bool walkable;
	enum tile_type type;
};

enum tile_type get_tile(float elevation);

struct tile **create_map(void);
struct position setup_map(struct tile **map);
void free_map(struct tile **map);

#endif
