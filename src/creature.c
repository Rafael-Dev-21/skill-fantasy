#include <stdlib.h>

#include "move.h"
#include "creature.h"

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

void creature_move_by(Creature *creature, Map *map)
{
	if (creature == NULL) {
		return;
	}
	if (map == NULL) {
		return;
	}
	Point cell = creature->position;
	move_from(&cell, creature->facing);
	Brain *brain = creature->brain;
	brain->enter(creature, map, cell);
}

void free_creature(Creature *creature)
{
	free(creature);
	creature = NULL;
}
