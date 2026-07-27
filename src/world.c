#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "skfantasy.h"
#include "noise.h"
#include "util.h"

void init_world(World * world, long seed)
{
	if (world == NULL) {
		return;
	}

  const float POLES   = 0.8f;
  const float EQUATOR = 0.2f;

	FBMParams params = default_fbm;
	params.noisefn = simplex2d;
	params.amplitude = 0.5;
	params.octaves = 3;

	for (int j = 0; j < WORLD_HEIGHT; j += 1) {
		for (int i = 0; i < WORLD_WIDTH; i += 1) {
			Tile *tile = tile_at(world, (Point){i, j});
			if (tile == NULL) {
				return;
			}
      float nx = (i+seed%0x7ffff) / 64.0 - 0.5;
      float ny = j / 64.0 - 0.5;
      float e = fbm2d(nx, ny, params);
      e = fbm2d(nx+e, ny+e, params);
      float m = fbm2d(nx+1000, ny, params);
      float t = e * e + POLES + (EQUATOR-POLES) * sinf(3.14159f * j / WORLD_HEIGHT);
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
        size_t c = world->moist_buf;
        world->moist_bufs[c][j][i] = 32;
      }
		}
	}
}

Tile *tile_at(World * world, Point cell)
{
  if (!world
      || cell.x < 0 || cell.y < 0
      || cell.x >= WORLD_WIDTH
      || cell.y >= WORLD_HEIGHT)
  {
    return NULL;
  }
	return &world->tiles[cell.y][cell.x];
}

Creature *creature_at(World *world, Point cell)
{
  if (!world
      || cell.x < 0 || cell.y < 0
      || cell.x >= WORLD_WIDTH
      || cell.y >= WORLD_HEIGHT)
  {
    return NULL;
  }
  size_t len = world->creature_count;
  for (size_t i = 0; i < len; ++i) {
    Creature *it = world->creatures + i;
    if (it->position.x == cell.x
        && it->position.y == cell.y)
    {
      return it;
    }
  }
  return NULL;
}

void place_wall(World * world, Point cell)
{
  if (!world
      || cell.x < 0 || cell.y < 0
      || cell.x >= WORLD_WIDTH
      || cell.y >= WORLD_HEIGHT)
  {
    return;
  }
	tile_at(world, cell)->object = OBJ_WALL;
}

void break_wall(World * world, Point cell)
{
  if (!world
      || cell.x < 0 || cell.y < 0
      || cell.x >= WORLD_WIDTH
      || cell.y >= WORLD_HEIGHT)
  {
    return;
  }
	tile_at(world, cell)->object = OBJ_NONE;
}

void try_toil(World *world, Point cell)
{
  if (!world
      || cell.x < 0 || cell.y < 0
      || cell.x >= WORLD_WIDTH
      || cell.y >= WORLD_HEIGHT)
  {
    return;
  }
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

Creature *get_creature_rand_empty(World *world)
{
	if (world == NULL) {
		return NULL;
	}
  Creature *creature = create_creature(world);
	if (creature == NULL) {
		return NULL;
	}

	Point cell;
	
	do {
		cell.x = rand() % WORLD_WIDTH;
		cell.y = rand() % WORLD_HEIGHT;
	} while (is_solid(tile_at(world, cell)) || creature_at(world, cell));

	creature->position = cell;

	return creature;
}

void world_remove(World *world, Creature *creature)
{
  int idx;
  int len = world->creature_count;
  for (idx = 0; idx < len; idx++) {
    if (&world->creatures[idx] == creature)
      break;
  }
  if (idx >= len)
    return;

  Creature *tmp = &world->creatures[len-1];
  world->creatures[idx] = *tmp;
  world->creature_count--;
}

static inline bool InBounds(int x, int y)
{
  return x >= 0 && y >= 0 && x < WORLD_WIDTH && y < WORLD_HEIGHT;
}

int world_update(World *w, Creature *p)
{
  if (w == NULL)
    return 1;
  if (p == NULL)
    return 1;

  // MOISTURE UPDATE
  size_t mcur = w->moist_buf;
  size_t mnew = 1-w->moist_buf;
  for (int y = 0; y < WORLD_HEIGHT; ++y) {
    for (int x = 0; x < WORLD_WIDTH; ++x) {
      Tile *t = tile_at(w, (Point){x, y});
      if (t->type == TILE_WATER) {
        w->moist_bufs[mnew][y][x] = 32;
      } else {
        int i = 0, d = 0;
        for (int dy = -1; dy < 2; ++dy) {
          for (int dx = -1; dx < 2; ++dx) {
            if ((dy || dx) && InBounds(x+dx, y+dy)) {
              i += w->moist_bufs[mcur][y+dy][x+dx];
              d += 2;
            }
          }
        }
        i /= d ? d : 1;
        w->moist_bufs[mcur][y][x] = i;
      }
    }
  }
  {
    size_t tmp = mcur;
    mcur = mnew;
    mnew = tmp;
  }
  for (int y = 0; y < WORLD_HEIGHT; ++y) {
    for (int x = 0; x < WORLD_WIDTH; ++x) {
    // GROWTH UPDATE
      Tile *t = tile_at(w, (Point){x, y});
      uint8_t moist = w->moist_bufs[mcur][y][x];
      if (obj_types[t->object].grow.enabled)
        t->growtime += rand()%3;
      else
        t->growtime = 0;
    // CHANGE UPDATE
      if (obj_types[t->object].grow.enabled && t->growtime > obj_types[t->object].grow.threshold)
        t->object = obj_types[t->object].grow.turnto;
      if (tile_types[t->type].highmoist.enabled && moist > tile_types[t->type].highmoist.threshold)
        t->type = tile_types[t->type].highmoist.turnto;

      if (tile_types[t->type].lowmoist.enabled && moist < tile_types[t->type].lowmoist.threshold)
        t->type = tile_types[t->type].lowmoist.turnto;
    }
  }

  // CREATURE UPDATES
  size_t len = w->creature_count;
	for (size_t i = 0; i < len; ++i) {
    Creature *it = w->creatures+i;
    creature_update(it, w);
	}

  // CREATURE DEATHS
  len = w->creature_count;
	for (size_t i = 0; i < len; ++i) {
    Creature *it = w->creatures+i;
	  int ohrt = get_stat_value(it, STAT_HRT);
	  int bohrt = get_base_stat_value(it, STAT_HRT);
    if (ohrt < HRT_DEAD(bohrt) || !it->is_alive) {
      if (it == p) {
        return 1;
      }
		  world_remove(w, it);
		  --i;
	  }
  }
  return 0;
}
