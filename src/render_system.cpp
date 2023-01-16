#include "common.hpp"
#include "render_system.hpp"

#define RENDER_MASK (COMPONENT_POS | COMPONENT_DRAW)

void renderSystem(Game *game)
{
    std::size_t entity;
    Position *pos;
    Draw *draw;

    for (entity = 0; entity < ENTITY_COUNT; ++entity)
    {
        if ((game->world.masks[entity] & RENDER_MASK) == RENDER_MASK) {
            pos = &(game->world.positions[entity]);
            draw = &(game->world.draws[entity]);

            mvaddch(pos->y - game->viewport.top, pos->x - game->viewport.left, draw->ch | COLOR_PAIR(draw->color));
        }
    }
}
