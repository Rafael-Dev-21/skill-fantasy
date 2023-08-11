#include <cmath>
#include <ctime>
#include <ncurses.h>

#include "engine.hpp"

EngineState genAction()
{
	clear();
	srand(50);
	mvaddstr(5, COLS / 2 - 8, "Creating world...");

	level = new Level();
	player = new Entity(IPoint(10, 10), '@', 5);

	clear();

	return ENGINE_PLAY;
}
