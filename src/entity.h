#pragma once

#define ENTITY_COUNT 256

typedef enum {
    COMPONENT_NONE = 0,
    COMPONENT_POS = 1 << 0,
    COMPONENT_HEALTH = 1 << 1,
    COMPONENT_DRAW = 1 << 2
} Component;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int health;
} Health;

typedef struct {
    char ch;
    int color;
} Draw;

typedef struct {
    int mask[ENTITY_COUNT];
    Position pos[ENTITY_COUNT];
    Health health[ENTITY_COUNT];
    Draw draw[ENTITY_COUNT];
    Position cam;
} World;

unsigned int createEntity(World *world);
void destroyEntity(World *world, unsigned int entity);

void renderSystem(World *world);
