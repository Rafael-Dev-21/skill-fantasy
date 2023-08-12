#include <curses.h>

#include "engine.hpp"

static void renderAll()
{
	if (player && level) {
	auto center = IPoint(COLS / 2, LINES / 2);

	auto origin = player->getPosition() - center;

	level->render(origin);
	player->render(origin);
	}
}

static void movePlayer(int x, int y) {
    player->move(Vector(x, y));
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
