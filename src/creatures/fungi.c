#include <stdlib.h>

#include "skfantasy.h"

#define SPREAD_MAX_COUNT 5
#define SPREAD_DIAMETER 11
#define SPREAD_RADIUS 5
#define SPREAD_CHANCE 2

static void fungi_update(Creature*, World*);
static void fungi_spread(Creature*, World*);

struct Fungi {
  Creature base;
	int8_t spread_count;
};

#define AS_CREATURE(fungi) ((Creature *)(fungi))
#define AS_FUNGI(creature) ((struct Fungi*)(creature))

static size_t my_brain;

void init_fungi_module(void)
{
  my_brain = brain_cnt++;
  brains[my_brain].update = &fungi_update;
  brains[my_brain].enter = &creature_default_enter;
}

Creature *create_fungi(World *world)
{
	if (world == NULL) {
		return NULL;
	}
	struct Fungi *fungi = AS_FUNGI(create_creature(sizeof(struct Fungi)));
	if (fungi == NULL) {
		return NULL;
	}
  fungi->spread_count = 0;
  AS_CREATURE(fungi)->brain = my_brain;
	
	for (int i = STAT_STR; i < STAT_HRT; i++) {
		AS_CREATURE(fungi)->stats[i].base = MIN_STAT + rand() % MAX_STAT;
	}
	AS_CREATURE(fungi)->stats[STAT_HRT].base = MIN_BASE_HRT + rand()%8;
	
	AS_CREATURE(fungi)->facing = rand()%4;
	AS_CREATURE(fungi)->glyph = 'f';
	AS_CREATURE(fungi)->color = 3;
	
	add_creature_rand_empty(world, AS_CREATURE(fungi));
	
	return AS_CREATURE(fungi);
}

static void fungi_update(Creature* fungi, World* world)
{
	if (fungi == NULL)
	{
		return;
	}
	if (world == NULL)
	{
		return;
	}

	if (((struct Fungi *)fungi)->spread_count < SPREAD_MAX_COUNT && (rand()%100) < SPREAD_CHANCE) {
		fungi_spread(fungi, world);
	}
}

static void fungi_spread(Creature* fungi, World* world)
{
	if (fungi == NULL) {
		return;
	}

	if (world == NULL) {
		return;
	}
	
	int x = fungi->position.x + (rand()%SPREAD_DIAMETER) - SPREAD_RADIUS;
	int y = fungi->position.y + (rand()%SPREAD_DIAMETER) - SPREAD_RADIUS;
	
	Tile *tile = tile_at(world, (Point){x, y});

	if (is_solid(tile) || creature_at(world, (Point){x, y})) {
		return;
	}
	
	Creature *child = create_fungi(world);
	if (child == NULL) {
		return;
	}
	child->position.x = x;
	child->position.y = y;
	
	((struct Fungi *)fungi)->spread_count++;
}

