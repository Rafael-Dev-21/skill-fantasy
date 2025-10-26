#ifndef WORLD_H
#define WORLD_H
#include "skfantasy.h"
#include <stdint.h>
typedef struct World World;
typedef uint32_t EntityId;

World *world_create(int width, int height);
void world_destroy(World *w);
void world_tick(World *w, int ticks);

EntityId word_spawn_creature(World *w, int x, int y, int type);
void world_remove_entity(World *w, EntityId e);

int world_get_tile(World *w, int x, int y);
void world_set_tile(World *w, int x, int y, int tile);

int world_save(World *w, const char *path);
World *world_load(const char *path);
#endif
