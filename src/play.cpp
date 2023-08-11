#include <ncurses.h>

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

static EngineState handleInput()
{
	IVector dir;

	switch(getch()) {
	case 'q':
		delete level; level = nullptr;
		delete player; player = nullptr;
		return ENGINE_TITLE;
	case 'h':
		dir.x = -1;
		break;
	case 'j':
		dir.y = 1;
		break;
	case 'k':
		dir.y = -1;
		break;
	case 'l':
		dir.x = 1;
		break;
	}

	player->move(dir);

	return ENGINE_PLAY;
}

EngineState playAction()
{
	renderAll();

	return handleInput();
}
