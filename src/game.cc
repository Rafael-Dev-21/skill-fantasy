#include "game.hh"
#include "callbacks.hh"

Game *Game::instance{nullptr};

Game::Game(): running(true) {
	machine.push(&onstart);
}

void Game::run() {
	while(running) {
		machine.top()();
	}
}

void Game::run_set(bool flag) {
	running = flag;
}

Game *Game::getInstance() {
	if(instance == nullptr) {
		instance = new Game();
	}
	
	return instance;
}
