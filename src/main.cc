#include "game.hh"
#include "commons.hh"
#include <iostream>
#include "callbacks.hh"

int main() {
	Game *game = Game::getInstance();

	initscr();
	noecho();
	game->run();
	endwin();

	return 0;
}
