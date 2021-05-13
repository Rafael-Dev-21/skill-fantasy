#include "callbacks.hh"
#include "fileio.hh"
#include <iostream>
#include <thread>
#include <chrono>
#include "commons.hh"

bool temp;

static std::string input;
static std::string menu_start_path("data/menu_start.txt");
static std::vector<std::string> menu_start;

static int y = 10;
static int x = 0;

std::string get_line() {
        std::string input;

	nocbreak();
	echo();

	int ch = getch();

	while(ch != '\n') {
		input.push_back(ch);
		ch = getch();
	}

	cbreak();
	noecho();

	return input;
}

int print_vcent(int y, std::string text) {
	int centx = (COLS - text.length())/2;
	mvaddstr(y, centx, text.c_str());

	return centx;
}

void pressanykey() {
	y++;
	print_vcent(y, "[Press any key to continue]");
	refresh();
	getch();
}

void onstart() {
	clear();
	box(stdscr, '=', '#');
	if(menu_start.empty()) {
		FileIO::load_file(menu_start, menu_start_path);
	}

	y = 10;
	for(std::string i : menu_start) {
		x = print_vcent(y, i);
		y++;
	}
	
	mvaddstr(y, x, "=> ");
	refresh();
	input = get_line();
	y++;

	if(input == "1" || input == "start") {
		print_vcent(y, "Not implemented yet!");
		pressanykey();
	} else if(input == "99" || input == "exit") {
		pressanykey();
		Game::getInstance()->run_set(false);
	} else if(input == "skill") {
		print_vcent(y, "Skills show ours capabilities.");
		pressanykey();
	} else if(input == "fantasy") {
		print_vcent(y, "The FANTASY never ends.");
		y++;
		print_vcent(y, "It's like a good dream.");
		y++;
		print_vcent(y, "You believe in dreams?(y/n) ");
		refresh();
		input = get_line();
		y++;
		if(input == "y") {
			print_vcent(y, "Good decision");
			pressanykey();
		} else if(input == "n") {
			print_vcent(y, "Bad decision");
			pressanykey();
			Game::getInstance()->run_set(false);
		} else {
			print_vcent(y, "What's that?");
			pressanykey();
		}
	} else if(input == "xyzzy") {
		print_vcent(y, "Greetings! you win!");
		move(y+1, x);
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		for(int i = 0; i < 5; i++) {
			y++;
			print_vcent(y, "Now play the damn game!");
			refresh();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		pressanykey();
	} else {
		mvaddstr(y, x, "Invalid option!");
		pressanykey();
	}
}
