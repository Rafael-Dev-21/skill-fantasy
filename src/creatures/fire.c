#include <stdlib.h>

#include "skfantasy.h"

#define SPREAD_MAX_COUNT 12
#define SPREAD_CHANCE 62

#define LIFE_MAX 11
#define LIFE_MIN 10

static void fire_spread(Creature*, World*);

Creature *create_fire(World *world, Point cell)
{
	if (world == NULL) {
		return NULL;
	}
	
  Tile *tile = tile_at(world, cell);
  if (is_flammable(tile)) {
    tile->object = OBJ_NONE;
  }
  Creature *c = creature_at(world, cell);
  if (c && c->is_flammable) {
    c->is_alive = false;
  }

	Creature *fire = create_creature(world);
	if (fire == NULL) {
		return NULL;
	}

  fire->kind = CFIRE;
	
	for (int i = STAT_STR; i < STAT_HRT; i++) {
		fire->stats[i].base = 0;
    fire->stats[i].modifier = 0;
	}
  fire->stats[STAT_HRT].base = LIFE_MIN;
	fire->stats[STAT_HRT].modifier = rand()%LIFE_MAX;
  fire->stats[STAT_STR].base = 4;
	
	fire->facing = rand()%4;
	fire->glyph = 'f';
	fire->color = 2;
  fire->is_flammable = false;
  fire->position = cell;

	return fire;
}

void fire_update(Creature* fire, World* world)
{
	if (fire == NULL)
	{
		return;
	}
	if (world == NULL)
	{
		return;
	}

  fire->facing = (fire->facing + rand()%4)%4;
	if (fire->spread_count < SPREAD_MAX_COUNT && (rand()%100) < SPREAD_CHANCE) {
		fire_spread(fire, world);
	}

  fire->stats[STAT_HRT].modifier -= rand()%3;
}

static void fire_spread(Creature* fire, World* world)
{
	if (fire == NULL) {
		return;
	}

	if (world == NULL) {
		return;
	}

  Point cell = fire->position;
  move_from(&cell, fire->facing);
	
	Tile *tile = tile_at(world, cell);

	if (!is_flammable(tile) && (!creature_at(world, cell) || !creature_at(world, cell)->is_flammable)) {
		return;
	}
	
	
	Creature *child = create_fire(world, cell);
	if (child == NULL) {
		return;
	}
	
	fire->spread_count++;
}

