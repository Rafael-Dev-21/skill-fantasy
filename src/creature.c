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

Creature *create_creature(Brain *brain)
{
	Creature *result = (Creature*)malloc(sizeof(Creature));
	if (result == NULL) {
		return NULL;
	}

	result->brain = brain;
	result->next = NULL;
	return result;
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
	Brain *brain = creature->brain;
	if (brain == NULL) {
		return;
	}
	Creature *other = creature_at(world, cell);
	if (other == NULL) {
		brain->enter(creature, world, cell);
	} else {
		creature_attack(creature, other, world);
	}
}

void free_creature(Creature *creature)
{
	if (creature == NULL) {
		return;
	}
	if (creature->brain != NULL) {
		free(creature->brain->data);
	}
	free(creature->brain);
	creature->brain = NULL;
	free(creature);
	creature = NULL;
}

void creature_attack(Creature *a, Creature *b, World *world)
{
	int str = get_stat_value(a, STAT_STR);
	int dmg = (rand()%str + rand()%str);
	if (dmg <= 0) {
		dmg = 1;
	}
	apply_modifier(b, STAT_HRT, -dmg);
	
	int ohrt = get_stat_value(b, STAT_HRT);
	int bohrt = get_base_stat_value(b, STAT_HRT);
	if (ohrt < HRT_DEAD(bohrt)) {
		world_remove(world, b);
		free_creature(b);
	}
}

void creature_default_enter(Creature *creature, World *world, Point cell)
{}

void creature_default_update(Creature *creature, World *world)
{}
