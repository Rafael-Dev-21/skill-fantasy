#include <stdlib.h>

#include "skfantasy.h"

int8_t get_base_stat_value(Creature const * const creature, StatId stat)
{
	if (creature == NULL) {
		return 0;
	}
	if (stat == STATS_COUNT) {
		return 0;
	}
	
	Stat const * stats = creature->stats;
	int result = stats[stat].base;
	
	if (stat != STAT_HRT) {
		return result < MIN_STAT ? MIN_STAT : result > MAX_STAT ? MAX_STAT : result;
	}

	return result;
}

int8_t get_stat_value(Creature const * const creature, StatId stat)
{
	if (creature == NULL) {
		return 0;
	}
	if (stat == STATS_COUNT) {
		return 0;
	}

	int result = creature->stats[stat].base;
	result += creature->stats[stat].modifier;
	
	if (stat != STAT_HRT) {
		return result < MIN_STAT ? MIN_STAT : result > MAX_STAT ? MAX_STAT : result;
	}

	return result;
}

void apply_modifier(Creature * creature, StatId stat, int8_t modifier)
{
	if (creature == NULL) {
		return;
	}
	if (stat == STATS_COUNT) {
		return;
	}

	creature->stats[stat].modifier += modifier;
}

Creature *create_creature(World *world)
{
  if (world == NULL)
    return NULL;
  if (world->creature_count >= MAX_CREATURES)
    return NULL;
  Creature *it = world->creatures;
  it += world->creature_count++;
  memset(it, 0, sizeof(*it));
  it->is_alive = true;
  return it;
}

void creature_move_by(Creature *creature, World *world)
{
	if (creature == NULL) {
		return;
	}
	if (world == NULL) {
		return;
	}
	Point cell = creature->position;
	move_from(&cell, creature->facing);
	Creature *other = creature_at(world, cell);
	if (other == NULL) {
		switch (creature->kind) {
    case CPLAYER:
      player_enter(creature, world, cell);
      break;
    case CBAT:
      bat_enter(creature, world, cell);
      break;
    default:
      creature_default_enter(creature, world, cell);
      break;
    }
	} else {
		creature_attack(creature, other, world);
	}
}

void creature_attack(Creature *a, Creature *b, World *world)
{
  (void)world;
	int str = get_stat_value(a, STAT_STR);
	int dmg = (rand()%str + rand()%str);
	if (dmg <= 0) {
		dmg = 1;
	}
	apply_modifier(b, STAT_HRT, -dmg);	
}

void creature_update(Creature *c, World *w)
{
  if (c == NULL)
    return;
  if (w == NULL)
    return;
	switch (c->kind) {
  case CFUNGI:
    fungi_update(c, w);
    break;
  case CFIRE:
    fire_update(c, w);
    break;
  case CBAT:
    bat_update(c, w);
    break;
  default:
    creature_default_update(c, w);
    break;
  }
}

#define UNUSED(x) ((void)(x))

void creature_default_enter(Creature *creature, World *world, Point cell)
{
  UNUSED(creature);
  UNUSED(world);
  UNUSED(cell);
}

void creature_default_update(Creature *creature, World *world)
{
  UNUSED(creature);
  UNUSED(world);
}

#undef UNUSED
