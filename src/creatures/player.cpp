#include <cstdlib>

#include "skfantasy.hpp"

static void player_enter(Creature *creature, World *world, Point cell);

CreatureHandle CreatureFactory::makePlayer()
{
  Creature p{};
  p.glyph = '@';
  p.color = colorpack(210, 210, 50);
  p.is_flammable = true;
  for (int i = STAT_STR; i < STAT_HRT; i++) {
    p.stats[i].base = ((rand()%6) + (rand()%6) + 2) / 2;
  }
	p.stats[STAT_HRT].base = 4 + ((rand() % 6) + (rand() % 6));
	p.facing = UP;
  p.is_flammable = true;
  p.is_alive = true;
  auto ht = add_creature_rand_empty(world, std::move(p));
  auto& stored = world->creatures.get(ht);
  stored.brain = std::make_unique<PlayerBrain>(world, ht);

  return stored.handle;
}

/*
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
  player->is_flammable = true;

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
}*/

void PlayerBrain::enter(Point cell)
{
  if (cell.x < 0 || cell.y < 0 || cell.x >= world->width || cell.y >= world->height)
    return;
  auto& p = world->creatures.get(creature);
  auto tile = tile_at(world, cell);

  auto oid = p.position.x + p.position.y * world->width;
  auto nid = cell.x + cell.y * world->width;
  if (!is_solid(tile)) {
    p.position.x = cell.x;
    p.position.y = cell.y;
    world->spatial_cache[oid] = {};
    world->spatial_cache[nid] = p.handle;
  }
}

void PlayerBrain::update()
{}
