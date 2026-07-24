#include <cstdlib>

#include "skfantasy.hpp"

CreatureHandle CreatureFactory::makeBat()
{
  Creature b{};
  b.glyph = 'b';
  b.color = colorpack(210, 210, 50);
  b.is_flammable = true;
  for (int i = STAT_STR; i < STAT_HRT; i++) {
    b.stats[i].base = MIN_STAT + rand()%3;
  }
	b.stats[STAT_HRT].base = MIN_BASE_HRT + rand()%2;
	b.facing = static_cast<Direction>(rand()%4);
  b.is_alive = true;
  auto ht = add_creature_rand_empty(world, std::move(b));
  auto& stored = world->creatures.get(ht);
  stored.brain = std::make_unique<BatBrain>(world, ht);

  return stored.handle;
}

/*
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
  bat->is_flammable = true;
	
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
*/

void BatBrain::enter(Point cell)
{
  if (cell.x < 0 || cell.y < 0 || cell.x >= world->width || cell.y >= world->height)
    return;
  auto tile = tile_at(world, cell);
  if (tile == nullptr)
    return;
  auto& b = world->creatures.get(creature);
  auto oidx = b.position.x + b.position.y * world->width;
  auto nidx = cell.x + cell.y * world->width;
  if (!is_solid(tile)) {
    b.position.x = cell.x;
    b.position.y = cell.y;
    world->spatial_cache[oidx] = {};
    world->spatial_cache[nidx] = b.handle;
  }
}

void BatBrain::update()
{
  auto& b = world->creatures.get(creature);
  b.facing = static_cast<Direction>((b.facing + rand()%4)%4);
  creature_move_by(&b, world);
}
