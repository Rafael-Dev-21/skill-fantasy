#include <stdlib.h>

#include "creature.h"
#include "factories.h"

static void player_enter(Creature *creature, Map *map, Point cell);

static Brain player_brain = {&player_enter};

Creature *create_player(Map *map)
{
	if (map == NULL) {
		return NULL;
	}
	Creature *player = create_creature(&player_brain);
	if (player == NULL) {
		return NULL;
	}
	player->glyph = '@';
	player->color = 4;

	int x = 0, y = 0;

	do {
		x = rand() % map->width;
		y = rand() % map->height;
	} while (is_solid(map, (Point){x, y}));

	for (int i = STAT_STR; i < STAT_HRT; i++) {
		player->stats[i].base = ((rand() % 6) + (rand() % 6) + 2) / 2;
	}

	player->stats[STAT_HRT].base = 4 + ((rand() % 6) + (rand() % 6));

	player->position = (Point){x, y};
	player->facing = UP;

	return player;
}

void player_enter(Creature *player, Map *map, Point cell)
{
	if (!is_solid(map, cell)) {
		player->position.x = cell.x;
		player->position.y = cell.y;
	}
}
