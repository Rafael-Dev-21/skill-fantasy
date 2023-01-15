#include <ncurses.h>
#include "game.h"
#include "colors.h"

bool gameInit(Game *game)
{
    initscr();
    noecho();
    curs_set(0);

    if (!has_colors()) return false;

    start_color();

    initPairs();

    game->world.cam.x = 0;
    game->world.cam.y = 0;

    genOverworld(&game->level);
    for (int i = 0; i < ENTITY_COUNT; i++) {
        destroyEntity(&game->world, i);
    }

    return true;
}

void processInput(Game *game, int ch)
{

}

void update(Game *game)
{

}

void render(Game *game)
{
    clear();
    Rect view;
    view.left = game->world.cam.x;
    view.top = game->world.cam.y;
    view.right = view.left + COLS;
    view.bottom = view.top + LINES;

    renderLevel(&game->level, view);
    renderSystem(&game->world);

    refresh();
}

void gameLoop(Game *game)
{
    int ch = ' ';
    while (ch != 'q') {
        processInput(game, ch);
        update(game);
        render(game);

        ch = getch();
    }
}

void gameClose(Game *game) {
    endwin();
}
