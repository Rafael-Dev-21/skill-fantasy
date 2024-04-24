#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

enum {
	TILE_NONE,
	TILE_GRASS,
	TILE_SAND,
	TILE_WATER,
	TILE_STONE,
	TILE_COUNT
};

enum {
	OBJ_NONE,
	OBJ_WALL,
	OBJ_COUNT
};

typedef struct {
	int glyph;
	int color;
} TileType;

typedef struct {
	int glyph;
	int color;
	bool solid;
} ObjectType;

typedef struct {
	int type;
	int object;
} Tile;

typedef struct {
	int width;
	int height;
	Tile * * tiles;
} Map;

// map
Map * create_map(int, int);
void free_map(Map *);
void init_map(Map *);
void place_wall(Map *, Point);
void break_wall(Map *, Point);
bool is_solid(Map * const, Point);

extern TileType tile_types[TILE_COUNT];
extern ObjectType obj_types[OBJ_COUNT];

#endif
