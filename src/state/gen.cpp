#include <cmath>
#include <chrono>
#ifdef __MINGW32__
#include "mingw.thread.h"
#else
#include <thread>
#endif
#include <curses.h>

#include "engine.hpp"

EngineState genAction()
{
    int cols, rows;

    getmaxyx(stdscr, rows, cols);

	clear();
	srand(50);
	mvaddstr(5, cols / 2 - 8, "Creating world...");
    refresh();

	level = new Level(1024, 1024);
	player = new Entity(IPoint(10, 10), '@', 5);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    mvaddstr(8, cols / 2 - 7, "[Press any key]");
    refresh();
    getch();

	clear();

	return ENGINE_PLAY;
}
