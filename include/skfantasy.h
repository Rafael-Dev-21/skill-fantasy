#ifndef SKFANTASY_H
#define SKFANTASY_H

/************
 * INCLUDES *
 ************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(_WIN32) || defined(__MINGW__)
#include <curses.h>
#else
#include <ncursesw/ncurses.h>
#endif

#include "arena.h"

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

#define CPLAYER 0
#define CFUNGI  1
#define CFIRE   2
#define CBAT    3

struct Creature {
	Stat stats[STATS_COUNT];
	int kind;
	Point position;
	Direction facing;
	int32_t glyph;
	int32_t color;
  int8_t spread_count;
  bool is_flammable;
  bool is_alive;
};

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
	uint8_t type;
	uint8_t object;
  uint16_t growtime;
} Tile;

#define WORLD_WIDTH 512
#define WORLD_HEIGHT 512
#define MAX_CREATURES 256

struct World {
	Tile tiles[WORLD_HEIGHT][WORLD_WIDTH];
  uint8_t moist_bufs[2][WORLD_HEIGHT][WORLD_WIDTH];
	Creature creatures[MAX_CREATURES];
  size_t creature_count;
  size_t moist_buf;
};

typedef struct {
  Arena *arena;
	Creature *player;
	World *world;
	char version[256];
} ModeData;

/**********
 * engine *
 **********/

void init_curses(void);

/********
 * draw *
 ********/

void draw_creature(Creature const * const creature, Point scroll);
void draw_world(World const * const world, Point scroll);

/********
 * move *
 ********/

void move_from(Point * pos, Direction dir);
Direction dir_from_ch(int ch, Direction fall);
Point point_from_dir(Direction dir);

/*********
 * modes *
 *********/

int start_mode(ModeData *data);
int generate_mode(ModeData *data);
int play_mode(ModeData *data);

/*********
 * stats *
 *********/

int8_t get_base_stat_value(Creature const * const creature, StatId id);
int8_t get_stat_value(Creature const * const creature, StatId id);
void apply_modifier(Creature * creature, StatId id, int8_t modifier);

/************
 * creature *
 ************/

Creature *create_creature(World *world);
void creature_move_by(Creature *creature, World *world);
void free_creature(Creature *creature);

void creature_attack(Creature *a, Creature *b, World *world);
void creature_update(Creature *a, World *world);

void player_enter(Creature*,World*, Point);
void bat_enter(Creature*,World*, Point);

void fungi_update(Creature*,World*);
void fire_update(Creature*,World*);
void bat_update(Creature*,World*);

/*********************
 * default behaviors *
 *********************/

void creature_default_enter(Creature *creature, World *world, Point cell);
void creature_default_update(Creature *creature, World *world);

/*********
 * world *
 *********/

void init_world(World *world, long seed);
Tile *tile_at(World *world, Point cell);
Creature *creature_at(World *world, Point cell);
void place_wall(World *world, Point cell);
void break_wall(World *world, Point cell);
void try_toil(World *world, Point cell);
bool is_solid(Tile * tile);
bool is_flammable(Tile *tile);
Creature *get_creature_rand_empty(World *world);
void world_remove(World *world, Creature *creature);
int world_update(World *world, Creature *player);

/*************
 * factories *
 *************/

Creature *create_player(World *world);
Creature *create_fungi(World *world);
Creature *create_bat(World *world);
Creature *create_fire(World *world, Point p);

/***********
 * EXTERNS *
 ***********/

extern TileType tile_types[TILE_COUNT];
extern ObjectType obj_types[OBJ_COUNT];

#endif
