#include "state/game_state.hh"
#include "commons.hh"
#include <iostream>

int main() {
	GameState game;

	std::cout << "Starting..." << std::endl;

	game.run();

	std::cout << "Closing..." << std::endl;

	return 0;
}

