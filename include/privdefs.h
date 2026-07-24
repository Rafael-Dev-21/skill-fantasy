#pragma once

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#include <stdbool.h>
#endif

/***********
 * DEFINES *
 ***********/

#define ESC 27

#define BASE_STAT 3
#define MIN_STAT 1
#define MAX_STAT 6

#define MIN_BASE_HRT 3
#define HRT_UNWELL 4
#define HRT_VERY_UNWELL 0
#define HRT_VULNERABLE(x) (-1 * (x))
#define HRT_DEAD(x) (-2 * (x))

/************
 * TYPEDEFS *
 ************/

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
} Direction;

typedef struct {
	int16_t x;
	int16_t y;
} Point;

typedef struct Creature Creature;
typedef struct World World;
typedef struct Brain Brain;

typedef enum {
	STAT_STR,
	STAT_MBL,
	STAT_MND,
	STAT_FTH,
	STAT_HRT,
	STATS_COUNT
} StatId;

typedef struct {
	int8_t base;
	int8_t modifier;
} Stat;

typedef enum {
	TILE_NONE,
	TILE_GRASS,
	TILE_SAND,
	TILE_WATER,
	TILE_STONE,
  TILE_SOIL,
  TILE_MUD,
	TILE_COUNT
} TileId;

typedef enum {
	OBJ_NONE,
	OBJ_WALL,
  OBJ_BUSH,
  OBJ_WHEAT_SEED,
  OBJ_WHEAT,
	OBJ_COUNT
} ObjectId;

typedef struct {
  bool enabled;
  int threshold;
  int turnto;
} CondValueChange;

typedef struct {
  bool enabled;
  TileId turnto;
} CondChange;

typedef struct {
	int32_t glyph;
	int32_t color;
  CondValueChange lowmoist;
  CondValueChange highmoist;
} TileType;

typedef struct {
	int32_t glyph;
	int32_t color;
	bool solid;
  // TODO: flammable can be a CondChange?
  bool flammable;
  CondValueChange grow;
} ObjectType;

typedef struct {
	TileId type;
	ObjectId object;
  int moisture;
  int growtime;
} Tile;

typedef struct ModeData ModeData;

/**********
 * engine *
 **********/

/********
 * draw *
 ********/

/********
 * move *
 ********/

void move_from(Point * pos, Direction dir);
Direction dir_from_ch(int ch, Direction fall);
Point point_from_dir(Direction dir);

/*********
 * modes *
 *********/

/*********
 * stats *
 *********/

int8_t get_base_stat_value(Creature const * const creature, StatId id);
int8_t get_stat_value(Creature const * const creature, StatId id);
void apply_modifier(Creature * creature, StatId id, int8_t modifier);

/************
 * creature *
 ************/

void creature_move_by(Creature *creature, World *world);
void free_creature(Creature *creature);

void creature_attack(Creature *a, Creature *b, World *world);
void creature_update(Creature *a, World *world);

/*********************
 * default behaviors *
 *********************/

void creature_default_enter(Creature *creature, World *world, Point cell);
void creature_default_update(Creature *creature, World *world);

/*********
 * world *
 *********/

World *create_world(int width, int height);
void free_world(World *world);
void init_world(World *world, long seed);
Tile *tile_at(World *world, Point cell);
Creature *creature_at(World *world, Point cell);
void place_wall(World *world, Point cell);
void break_wall(World *world, Point cell);
void try_toil(World *world, Point cell);
bool is_solid(Tile * tile);
bool is_flammable(Tile *tile);

/*************
 * factories *
 *************/

/*
Creature *create_player(World *world);
Creature *create_fungi(World *world);
Creature *create_bat(World *world);
Creature *create_fire(World *world, Point p);
*/

/***********
 * EXTERNS *
 ***********/

extern TileType tile_types[TILE_COUNT];
extern ObjectType obj_types[OBJ_COUNT];

#ifdef __cplusplus
}
#endif
