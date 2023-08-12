#include <curses.h>

#include "engine.hpp"

EngineAction Engine::actionTable[] = {
	&titleAction,
	&genAction,
	&playAction
};

Engine::Engine()
{
	initscr();
	noecho();
	curs_set(0);

	colors();

	state = ENGINE_TITLE;
}

Engine::~Engine()
{
	endwin();
}

void Engine::run()
{
	while (state != ENGINE_EXIT) {
		state = actionTable[state]();
	}
}

void Engine::colors()
{
	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_YELLOW, COLOR_GREEN);
		init_pair(2, COLOR_YELLOW, COLOR_WHITE);
		init_pair(3, COLOR_CYAN, COLOR_BLUE);
		init_pair(4, COLOR_BLACK, 8);
		init_pair(5, COLOR_RED, COLOR_MAGENTA);
	}
}
