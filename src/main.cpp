#include "game.hpp"
#include <math.h>

static void initColonist(World *world, int x, int y)
{
    std::size_t entity = world->newEntity();

    world->masks[entity] = COMPONENT_POS | COMPONENT_DRAW | COMPONENT_HEALTH;
    world->positions[entity].x = x;
    world->positions[entity].y = y;
    world->draws[entity].ch = '@';
    world->draws[entity].color = 0;
    world->healths[entity].health = 50;
}

int main() {
    Game game;
    if (!game.init()) {
        game.close();
        return -1;
    }

    for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / 12) {
        initColonist(&game.world, 10 + 2 * cos(i), 10 + 2 * sin(i));
    }

    game.loop();

    game.close();

    return 0;
}
