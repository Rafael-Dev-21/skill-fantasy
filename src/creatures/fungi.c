#include <stdlib.h>

#include "skfantasy.h"

#define SPREAD_MAX_COUNT 5
#define SPREAD_DIAMETER 11
#define SPREAD_RADIUS 5
#define SPREAD_CHANCE 2

static void fungi_spread(Creature*, World*);

struct FungiData {
	int8_t spread_count;
};

Creature *create_fungi(World *world)
{
	if (world == NULL) {
		return NULL;
	}

	Creature *fungi = get_creature_rand_empty(world);
	if (fungi == NULL) {
		return NULL;
	}

  fungi->kind = CFUNGI;
	
	for (int i = STAT_STR; i < STAT_HRT; i++) {
		fungi->stats[i].base = MIN_STAT + rand() % MAX_STAT;
	}
	fungi->stats[STAT_HRT].base = MIN_BASE_HRT + rand()%8;
	
	fungi->facing = rand()%4;
	fungi->glyph = 'f';
	fungi->color = 3;
  fungi->is_flammable = true;
	
	return fungi;
}

void fungi_update(Creature* fungi, World* world)
{
	if (fungi == NULL)
	{
		return;
	}
	if (world == NULL)
	{
		return;
	}

	if (fungi->spread_count < SPREAD_MAX_COUNT && (rand()%100) < SPREAD_CHANCE) {
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

	if (!tile || is_solid(tile) || creature_at(world, (Point){x, y})) {
		return;
	}
	
	Creature *child = create_fungi(world);
	if (child == NULL) {
		return;
	}
	child->position.x = x;
	child->position.y = y;

  child->spread_count = fungi->spread_count++;
}

