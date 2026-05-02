#include <stdlib.h>

#include "skfantasy.h"

#define SPREAD_MAX_COUNT 5
#define SPREAD_DIAMETER 11
#define SPREAD_RADIUS 5
#define SPREAD_CHANCE 2

static void bat_update(Creature*, World*);
static void bat_enter(Creature*, World*, Point);

Creature *create_bat(World *world)
{
	if (world == NULL) {
		return NULL;
	}

	Brain *brain = malloc(sizeof(Brain));
	if (brain == NULL) {
		return NULL;
	}
	brain->enter = &bat_enter;
	brain->update = &bat_update;
	brain->data = NULL;
	
	Creature *bat = create_creature(brain);
	if (bat == NULL) {
		free(brain);
		return NULL;
	}
	
	for (int i = STAT_STR; i < STAT_HRT; i++) {
		bat->stats[i].base = MIN_STAT + rand() % 3;
	}
	bat->stats[STAT_HRT].base = MIN_BASE_HRT + rand()%2;
	
	bat->facing = rand()%4;
	bat->glyph = 'b';
	bat->color = 4;
	
	add_creature_rand_empty(world, bat);
	
	return bat;
}

static void bat_update(Creature* bat, World* world)
{
	if (bat == NULL)
	{
		return;
	}
	if (world == NULL)
	{
		return;
	}

  bat->facing = (bat->facing + rand()%4)%4;
  creature_move_by(bat, world);
}

static void bat_enter(Creature* bat, World* world, Point cell)
{
	if (bat == NULL) {
		return;
	}

	if (world == NULL) {
		return;
	}
	
	Tile *tile = tile_at(world, cell);
	if (tile == NULL) {
		return;
	}

	if (!is_solid(tile)) {
		bat->position.x = cell.x;
		bat->position.y = cell.y;
  }
}

