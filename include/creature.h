#ifndef CREATURE_H
#define CREATURE_H

#include <stdint.h>

#include "position.h"
#include "map.h"

#define BASE_STAT 3
#define MIN_STAT 1
#define MAX_STAT 6

#define MIN_BASE_HRT 3
#define HRT_UNWELL 4
#define HRT_VERY_UNWELL 0
#define HRT_VULNERABLE(x) (-1 * (x))
#define HRT_DEAD(x) (-2 * (x))

typedef struct Creature Creature;

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

typedef struct {
	void (*enter)(struct Creature*, Map*, Point);
} Brain;

struct Creature {
	Stat stats[STATS_COUNT];
	Brain *brain;
	Point position;
	Direction facing;
	int glyph;
	int color;
	struct Creature *next;
};

/*********
 * Stats *
 *********/

int8_t get_base_stat_value(Creature const * const creature, StatId stat);
int8_t get_stat_value(Creature const * const creature, StatId stat);
void apply_modifier(Creature *creature, StatId stat, int8_t modifier);

/*************
 * Creatures *
 *************/
Creature *create_creature(Brain *brain);
void creature_move_by(Creature *creature, Map *map);
void free_creature(Creature *creature);
#endif
