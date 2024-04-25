#include <stdlib.h>

#include "skfantasy.h"

static void player_enter(Creature *creature, World *world, Point cell);

Creature *create_player(World *world)
{
	if (world == NULL) {
		return NULL;
	}
	Brain *brain = malloc(sizeof(Brain));
	if (brain == NULL) {
		return NULL;
	}

	brain->enter = &player_enter;
	brain->update = &creature_default_update;
	brain->data = NULL;

	Creature *player = create_creature(brain);
	if (player == NULL) {
		return NULL;
	}
	player->glyph = '@';
	player->color = 4;

	add_creature_rand_empty(world, player);

	for (int i = STAT_STR; i < STAT_HRT; i++) {
		player->stats[i].base = ((rand() % 6) + (rand() % 6) + 2) / 2;
	}

	player->stats[STAT_HRT].base = 4 + ((rand() % 6) + (rand() % 6));

	player->facing = UP;

	return player;
}

void player_enter(Creature *player, World *world, Point cell)
{
	if (player == NULL) {
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
		player->position.x = cell.x;
		player->position.y = cell.y;
	}
}
