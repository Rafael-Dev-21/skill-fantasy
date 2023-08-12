#include <curses.h>

#include "engine.hpp"

static void renderAll()
{
    int cols, rows;
    getmaxyx(stdscr, rows, cols);

	if (player && level) {
	auto center = IPoint(cols / 2, rows / 2);

	auto origin = player->getPosition() - center;

	level->render(origin);
	player->render(origin);
	}
}

static void movePlayer(int x, int y) {
    player->move(IVector(x, y));
    beep();
}

static EngineState handleInput()
{
	switch(getch()) {
	case 'q':
		delete level; level = nullptr;
		delete player; player = nullptr;
		return ENGINE_TITLE;
	case 'h':
		movePlayer(-1, 0);
		break;
	case 'j':
		movePlayer(0, 1);
		break;
	case 'k':
		movePlayer(0, -1);
		break;
	case 'l':
		movePlayer(1, 0);
		break;
	}
    return ENGINE_PLAY;
}

EngineState playAction()
{
	renderAll();

	return handleInput();
}
