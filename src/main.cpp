#include "engine.hpp"

#include <ncurses.h>

#include <cmath>

Level *level = nullptr;
Entity *player = nullptr;

int main(void)
{
	Engine game;

	game.run();

	delete level;
	delete player;
	
	return 0;
}
