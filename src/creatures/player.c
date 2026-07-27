#include <stdlib.h>

#include "skfantasy.h"

Creature *create_player(World *world)
{
	if (world == NULL) {
		return NULL;
	}

  Creature *player = get_creature_rand_empty(world);
	if (player == NULL) {
		return NULL;
	}

  player->kind = CPLAYER;

	player->glyph = '@';
	player->color = 4;
  player->is_flammable = true;

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
