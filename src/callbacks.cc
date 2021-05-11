#include "callbacks.hh"
#include "fileio.hh"
#include <iostream>

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

	if(input == "1") {
		std::cout << "Not inplemented yet!" << std::endl;
		pressanykey();
	} else if(input == "99") {
		Game::getInstance()->run_set(false);
	} else {
		std::cout << "Invalid option!" << std::endl;
		pressanykey();
	}
}
