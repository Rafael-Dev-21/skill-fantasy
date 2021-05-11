#include "game.hh"
#include "commons.hh"
#include <iostream>
#include "callbacks.hh"

int main() {
	Game *game = Game::getInstance();

	std::cout << "Starting..." << std::endl;

	game->run();

	std::cout << "Closing..." << std::endl;

	return 0;
}

