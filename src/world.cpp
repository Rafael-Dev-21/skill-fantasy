#include <cstdlib>
#include <cmath>
#include <cassert>

#include "skfantasy.hpp"
extern "C" {
#include "noise.h"
#include "util.h"
#include "rng32.h"
}

static int *world_moist_buffer(World *w, uint32_t other);

static size_t world_index(World *w, int x, int y)
{
  return x + w->width * y;
}

World * create_world(int width, int height)
{
	World * result = new World(); //(World *)calloc(1, sizeof(World));
	if (result == NULL) {
		return NULL;
	}

	result->width = width;
	result->height = height;
	/*result->tiles = (Tile *)calloc(result->height * result->width, sizeof(Tile));
	if (result->tiles == NULL) {
		free(result);
		return NULL;
	}*/
  result->tiles.resize(width * height);
  /*result->moisture_buffer1 = (int *)calloc(result->height * result->width, sizeof(int));
	if (result->moisture_buffer1 == NULL) {
    free(result->tiles);
		free(result);
		return NULL;
	}
	result->moisture_buffer2 = (int *)calloc(result->height * result->width, sizeof(int));
	if (result->moisture_buffer2 == NULL) {
    free(result->moisture_buffer1);
    free(result->tiles);
		free(result);
		return NULL;
  }*/
  result->moisture_buffer1.resize(width * height);
  result->moisture_buffer2.resize(width * height);
  result->current_moisture_buffer = 0;
	//result->creatures = NULL;
  result->spatial_cache.resize(width * height);

	return result;
}

void free_world(World * world)
{
	if (world == NULL) {
		return;
	}
/*
	free(world->tiles);
	free(world->moisture_buffer1);
	free(world->moisture_buffer2);

	Creature *it = world->creatures;
	while (it != NULL) {
		Creature *c = it;
		it = it->next;
		free_creature(c);
	}

	free(world);
	world = NULL;*/
  delete world;
}

void init_world(World * world, long seed)
{
	if (world == NULL) {
		return;
	}

  _rng32_seed = seed;
  rng32();
  rng32();

  const float POLES   = 0.8f;
  const float EQUATOR = 0.2f;

	FBMParams params = default_fbm;
	params.noisefn = simplex2d;
	params.amplitude = 0.5;
	params.octaves = 3;

  const size_t len = world->height * world->width;
#pragma omp parallel for
  for (size_t idx = 0; idx < len; idx++) {
    Tile *tile = &world->tiles[idx];
    const size_t i = idx % world->width;
    const size_t j = idx / world->width;
    float nx = (i+seed%0x7ffff) / 64.0 - 0.5;
    float ny = j / 64.0 - 0.5;
    float e = fbm2d(nx, ny, params);
    e = fbm2d(nx+e, ny+e, params);
    float m = fbm2d(nx+1000, ny, params);
    float t = e * e + POLES + (EQUATOR-POLES) * sinf(3.14159f * j / world->height);
    if        (e < 0.3f)
      tile->type = TILE_WATER;
    else if (e < 0.4f)
      tile->type = TILE_SAND;
    else if (e < 0.7f)
      tile->type = TILE_GRASS;
    else
		  tile->type = TILE_STONE;

    if        (tile->type == TILE_STONE && e >= 0.9) {
			tile->object = OBJ_WALL;
    } else if (tile->type == TILE_GRASS) {
      if      (((t <= 0.8 && t > 0.6 && m >= 0.33 && m < 0.66)
                || (t <= 0.6 && t > 0.3 && m >= 0.16 && m < 0.5))
                && ((hash_pos(i, j) % 100) < 35))
        tile->object = OBJ_BUSH;
      else
        tile->object = OBJ_NONE;
    }
    if (tile->type == TILE_WATER) {
      world_moist_buffer(world, 0)[idx] = 32;
		}
	}
}

Tile *tile_at(World * world, Point cell)
{
	if (world == NULL) {
		return NULL;
	}
	if (cell.x < 0) {
		return NULL;
	}
	if (cell.y < 0) {
		return NULL;
	}
	if (cell.x >= world->width) {
		return NULL;
	}
	if (cell.y >= world->height) {
		return NULL;
	}
	return &world->tiles[world_index(world, cell.x, cell.y)];
}

Creature *creature_at(World *world, Point cell)
{
  /*
	Creature *it = world->creatures;
	while (it != NULL) {
		if (it->position.x == cell.x &&
			it->position.y == cell.y) {
			return it;
		}
		it = it->next;
	}
	return NULL;*/
  /*
  for (auto& it : world->creatures) {
    if (it.position.x == cell.x
        && it.position.y == cell.y) {
      return &it;
    }
  }
  return nullptr;*/
  if (cell.x < 0 || cell.y < 0 || cell.x >= world->width || cell.y >= world->height)
    return nullptr;
  auto idx = cell.x + cell.y * world->width;
  auto ht = world->spatial_cache[idx];
  if (ht == HandleVector<Creature,Handle>::null_handle) {
    return nullptr;
  }
  auto& it = world->creatures.get(ht);
  return &it;
}

void place_wall(World * world, Point cell)
{
	if (world == NULL) return;
	if (cell.x < 0) return;
	if (cell.x >= world->width) return;
	if (cell.y < 0) return;
	if (cell.y >= world->height) return;
	tile_at(world, cell)->object = OBJ_WALL;
}

void break_wall(World * world, Point cell)
{
	if (world == NULL) return;
	if (cell.x < 0) return;
	if (cell.x >= world->width) return;
	if (cell.y < 0) return;
	if (cell.y >= world->height) return;
	tile_at(world, cell)->object = OBJ_NONE;
}

void try_toil(World *world, Point cell)
{
	if (world == NULL) return;
	if (cell.x < 0) return;
	if (cell.x >= world->width) return;
	if (cell.y < 0) return;
	if (cell.y >= world->height) return;
	Tile *t = tile_at(world, cell);
  if ((t->type != TILE_GRASS && t->type != TILE_MUD) || t->object != OBJ_NONE)
    return;
  if (t->type == TILE_GRASS)
    t->type = TILE_SOIL;
  else
    t->object = OBJ_WHEAT_SEED;
}

bool is_solid(Tile * tile)
{
	if (tile == NULL) {
		return false;
	}
	return obj_types[tile->object].solid;
}


bool is_flammable(Tile * tile)
{
	if (tile == NULL) {
		return false;
	}
	return obj_types[tile->object].flammable;
}

CreatureHandle add_creature_rand_empty(World *world, Creature&& creature)
{
	if (world == NULL) {
		return {};
	}
  /*
	if (creature == NULL) {
		return;
	}*/

	Point cell;
	
	do {
		cell.x = rng32() % world->width;
		cell.y = rng32() % world->height;
	} while (is_solid(tile_at(world, cell)) || creature_at(world, cell));

	creature.position = cell;

/*
	creature->next = world->creatures;
	world->creatures = creature;*/
  auto ht = world->creatures.add(std::move(creature));
  int idx = cell.x + cell.y * world->width;
  world->spatial_cache[idx] = ht;
  return ht;
}

void world_remove(World *world, CreatureHandle creature)
{
  /*
	Creature *it = world->creatures;
	if (creature == it) {
		world->creatures = it->next;
	} else {
		Creature *last = it;
		it = it->next;
		while (it != NULL) {
			if (creature == it) {
				last->next = it->next;
				return;
			}
			last = it;
			it = it->next;
		}
	}*/
  if (!world->creatures.has(creature)) {
    return;
  }
  auto& it = world->creatures.get(creature);
  int idx = it.position.x + it.position.y * world->width;
  if (world->spatial_cache[idx] == it.handle) {
    world->spatial_cache[idx] = {};
  }
  world->creatures.remove(creature);
}

static int *world_moist_buffer(World *w, uint32_t other) {
  assert(other < 2 && "other should be 1 or 2");
  if (other) {
    return w->current_moisture_buffer ? &w->moisture_buffer1[0] : &w->moisture_buffer2[0];
  } else {
    return w->current_moisture_buffer ? &w->moisture_buffer2[0] : &w->moisture_buffer1[0];
  }
}

static void world_flip_moist_buffer(World *w) {
  w->current_moisture_buffer = 1-w->current_moisture_buffer;
}

static inline int IN_BOUNDS(World *w, int x, int y)
{
  return x >= 0 && y >= 0 && w->width > x && w->height > y;
}

int world_update(World *w, CreatureHandle ph)
{
  if (w == NULL)
    return 1;
/*  if (p == NULL)
    return 1;*/
  if (!w->creatures.has(ph))
    return 1;
  auto& p = w->creatures.get(ph);

  // MOISTURE UPDATE
  int *new_moist = world_moist_buffer(w,1);
  int *old_moist = world_moist_buffer(w,0);
  for (int y = 0; y < w->height; ++y) {
    Tile *tr = &w->tiles[y*w->width];
    for (int x = 0; x < w->width; ++x) {
      Tile *t = &tr[x];
      int idx = world_index(w, x, y);
      if (t->type == TILE_WATER) {
        new_moist[idx] = 32;
      } else {
        int i = 0;
        int d = 0;
        for (int dy = -1; dy < 2; ++dy) {
          for (int dx = -1; dx < 2; ++dx) {
            if ((dy || dx) && IN_BOUNDS(w, x+dx, y+dy)) {
              int tidx = idx + dx + dy * w->width;
              i += old_moist[tidx];
              d += 1;
            }
          }
        }
        i /= d ? d : 1;
        new_moist[idx] = i;
      }
    }
  }
  world_flip_moist_buffer(w);
  int *cur_moist = world_moist_buffer(w, 0);
  for (int y = 0; y < w->height; ++y) {
    Tile *tr = &w->tiles[y*w->width];
    for (int x = 0; x < w->width; ++x) {
      Tile *t = &tr[x];
      ObjectType *obj = &obj_types[t->object];
      TileType *type = &tile_types[t->type];
      int idx = world_index(w, x, y);
      int moist = cur_moist[idx];
      // GROWTH UPDATE
      if (obj->grow.enabled)
        t->growtime += rng32()%3;
      else
        t->growtime = 0;
      // CHANGE UPDATE
      if (obj->grow.enabled && t->growtime > obj->grow.threshold)
        t->object = (ObjectId)obj->grow.turnto;
      if (type->highmoist.enabled && moist > type->highmoist.threshold)
        t->type = (TileId)type->highmoist.turnto;

      if (type->lowmoist.enabled && moist < type->lowmoist.threshold)
        t->type = (TileId)type->lowmoist.turnto;
    }
  }

  // CREATURE UPDATES
  /*
	Creature *it = w->creatures;
	while (it != NULL) {
    creature_update(it, w);
		it = it->next;
	}*/
  std::vector<Creature*> c;
  for (auto& it : w->creatures)
    if (it.handle != Handle{})
      c.push_back(&it);
  for (auto& it : c) {
    creature_update(it, w);
  }

  // CREATURE DEATHS
  //it = w->creatures;
//	while (it != NULL) {
  c.clear();
  for (auto& it : w->creatures)
    if (it.handle != Handle{})
      c.push_back(&it);
  for (auto& it : c) {
	  int ohrt = get_stat_value(it, STAT_HRT);
	  int bohrt = get_base_stat_value(it, STAT_HRT);
//    Creature *next = it->next;
    if (ohrt < HRT_DEAD(bohrt) || !it->is_alive) {
      if (it->handle == ph) {
        return 1;
      }
		  world_remove(w, it->handle);
//		  free_creature(it);
	  }
//    it = next;
  }
  return 0;
}
