#include <ncurses.h>
#include "entity.h"

unsigned int createEntity(World *world)
{
    unsigned int entity;
    for (entity = 0; entity < ENTITY_COUNT; ++entity) {
        if (world->mask[entity] == COMPONENT_NONE) {
            return entity;
        }
    }

    return (ENTITY_COUNT);
}

void destroyEntity(World *world, unsigned int entity)
{
    world->mask[entity] = COMPONENT_NONE;
}

#define RENDER_MASK (COMPONENT_POS | COMPONENT_DRAW)

void renderSystem(World *world)
{
    unsigned int entity;
    Position *pos;
    Draw *draw;
    for (entity = 0; entity < ENTITY_COUNT; ++entity) {
        if ((world->mask[entity] & RENDER_MASK) ==RENDER_MASK) {
            pos = &(world->pos[entity]);
            draw = &(world->draw[entity]);

            mvaddch(pos->y - world->cam.y, pos->x - world->cam.x, draw->ch | COLOR_PAIR(draw->color));
        }
    }
}
