#include "common.hpp"
#include "game.hpp"
#include "colors.hpp"

#include "render_system.hpp"

Game::Game() :
    level(128, 128)
{}

bool Game::init()
{
    initscr();
    noecho();
    curs_set(0);

    if (!has_colors()) return false;

    start_color();

    initPairs();

    viewport.top = 0;
    viewport.left = 0;
    viewport.right = COLS;
    viewport.bottom = LINES;

    level.genOverworld();

    return true;
}

void Game::processInput()
{
    int x = 0, y = 0;

    switch (currentInput) {
        case 'h':
            x = -1;
            break;
        case 'j':
            y = 1;
            break;
        case 'k':
            y = -1;
            break;
        case 'l':
            x = 1;
            break;
    }

    viewport.top += y;
    viewport.bottom += y;
    viewport.left += x;
    viewport.right += x;
}

void Game::update()
{

}

void Game::render()
{
    clear();
    level.render(viewport);
    renderSystem(this);
    refresh();
}

void Game::loop()
{
    while (currentInput != 'q') {
        processInput();
        update();
        render();

        currentInput = getch();
    }
}

void Game::close() {
    endwin();
}
