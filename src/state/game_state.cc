#include "game_state.hh"
#include "cstdlib"
#include <iostream>
#include <fstream>



static std::string input = "";
static std::string output = "";

void GameState::changeState(GameStateEnum n) {
	game_state = n;
}

static void on_start(GameState *current) {
#ifdef _WIN32
	system("cls");
#endif
#ifdef __linux__
	system("clear");
#endif

	std::ifstream menu("data/menu_start.txt");

	while(std::getline(menu, output)) {
		std::cout << output << std::endl;
	}

	menu.close();

	std::cout << "=> ";
	std::cin >> input;
	if(input == "1") {
		std::cout << "not implemented yet!" << std::endl;
		std::cout << "[press any key]" << std::endl;
#ifdef _WIN32
		system("pause");
#endif
#ifdef __linux__
		system("read -n1");
#endif
	} else if(input == "99") {
		current->changeState(STATE_END);
	} else {
		std::cout << "E: option not supported!" << std::endl;
		std::cout << "[press any key]" << std::endl;
#ifdef _WIN32
		system("pause");
#endif
#ifdef __linux__
		system("read -n 1");
#endif
	}
}

static void on_battle(GameState *current) {}

static void on_end(GameState *current) {}

GameState::GameState(): game_state(STATE_START) {}

GameState::GameState(GameStateEnum state): game_state(state) {}

void GameState::run() {
	while(true) {
		switch(game_state) {
			case STATE_START:
				on_start(this);
				break;
			case STATE_BATTLE:
				on_battle(this);
				break;
			default:
				break;
		}

		if(game_state == STATE_END) {
			on_end(this);
			break;
		}
	}
}
