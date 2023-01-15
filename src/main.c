#include "game.h"
#include <math.h>

static void initColonist(World *world, int x, int y)
{
    unsigned int entity = createEntity(world);

    world->mask[entity] = COMPONENT_POS | COMPONENT_DRAW | COMPONENT_HEALTH;
    world->pos[entity].x = x;
    world->pos[entity].y = y;
    world->draw[entity].ch = '@';
    world->draw[entity].color = 0;
    world->health[entity].health = 50;
}

int main() {
    Game game;
    if (!gameInit(&game)) {
        gameClose(&game);
        return -1;
    }

    for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / 12) {
        initColonist(&game.world, 10 + 2 * cos(i), 10 + 2 * sin(i));
    }

    gameLoop(&game);

    gameClose(&game);

    return 0;
}
