#include "callbacks.hh"
#include "fileio.hh"
#include <iostream>
#include <thread>
#include <chrono>

bool temp;

static std::string input("");
static std::string menu_start_path("data/menu_start.txt");
static std::vector<std::string> menu_start;

void pressanykey() {
	std::cout << "[press any key]" << std::endl;
#ifdef _WIN32
	system("pause");
#endif
#ifdef __linux__
	system("read -n 1");
#endif
}

void onstart() {
#ifdef _WIN32
	system("cls");
#endif
#ifdef __linux__
	system("clear");
#endif
	if(menu_start.empty()) {
		FileIO::load_file(menu_start, menu_start_path);
	}

	for(std::string i : menu_start) {
		std::cout << i << std::endl;
	}
	
	std::cout << "=> ";
	std::cin >> input;

	if(input == "1" || input == "start") {
		std::cout << "Not inplemented yet!" << std::endl;
		pressanykey();
	} else if(input == "99" || input == "exit") {
		Game::getInstance()->run_set(false);
	} else if(input == "skill") {
		std::cout << "Skills mark ours capacities" << std::endl;
		pressanykey();
	} else if(input == "fantasy") {
		std::cout << "The FANTASY never ends." << std::endl;
		std::cout << "It's like a good dream." << std::endl;
		std::cout << "You believe in dreams?(y/n) ";
		std::cin >> input;
		if(input == "y") {
			std::cout << "Good decision" << std::endl;
			pressanykey();
		} else if(input == "n") {
			std::cout << "Bad decision" << std::endl;
			Game::getInstance()->run_set(false);
		} else {
			std::cout << "What's that?" << std::endl;
			pressanykey();
		}
	} else if(input == "xyzzy") {
		std::cout << "Greetings! you win!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		for(int i = 0; i < 5; i++) {
			std::cout << "Now play the damn game!" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		pressanykey();
	} else {
		std::cout << "Invalid option!" << std::endl;
		pressanykey();
	}
}
