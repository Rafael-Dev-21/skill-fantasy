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
	STAT_FHT,
	STAT_HRT,
	STATS_COUNT
} StatId;

typedef struct {
	int8_t base;
	int8_t modifier;
} Stat;

struct Creature {
	Stat stats[STATS_COUNT];
	Creature *next;
	Point position;
	Direction facing;
	int32_t glyph;
	int32_t color;
  uint8_t brain;
};

typedef enum {
	TILE_NONE,
	TILE_GRASS,
	TILE_SAND,
	TILE_WATER,
	TILE_STONE,
	TILE_COUNT
} TileId;

typedef enum {
	OBJ_NONE,
	OBJ_WALL,
	OBJ_COUNT
} ObjectId;

typedef struct {
	int32_t glyph;
	int32_t color;
} TileType;

typedef struct {
	int32_t glyph;
	int32_t color;
	bool solid;
} ObjectType;

typedef struct {
	TileId type;
	ObjectId object;
} Tile;

struct World {
	int16_t width;
	int16_t height;
	Tile *tiles;
	Creature *creatures;
};

typedef struct {
	void (*enter)(Creature*, World*, Point);
	void (*update)(Creature*, World*);
} Brain;

typedef struct {
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

Creature *create_creature(size_t size);
void creature_move_by(Creature *creature, World *world);
void free_creature(Creature *creature);

void creature_attack(Creature *a, Creature *b, World *world);

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
void init_world(World *world);
Tile *tile_at(World *world, Point cell);
Creature *creature_at(World *world, Point cell);
void place_wall(World *world, Point cell);
void break_wall(World *world, Point cell);
bool is_solid(Tile * tile);
void add_creature_rand_empty(World *world, Creature *creature);
void world_remove(World *world, Creature *creature);

/*************
 * factories *
 *************/

void init_fungi_module(void);
void init_player_module(void);

Creature *create_player(World *world);
Creature *create_fungi(World *world);

/***********
 * EXTERNS *
 ***********/

extern TileType tile_types[TILE_COUNT];
extern ObjectType obj_types[OBJ_COUNT];
extern Brain brains[];
extern size_t brain_cap;
extern size_t brain_cnt;

#endif
