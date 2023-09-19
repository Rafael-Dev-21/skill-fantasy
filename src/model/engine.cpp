#include "engine.hpp"

#include <curses.h>

EngineAction Engine::actionTable[] = {&titleAction, &genAction, &playAction};

Engine::Engine(bool blackBG) : blackBG(blackBG) {
  initscr();
  noecho();
  curs_set(0);

  colors();

  state = ENGINE_TITLE;
}

Engine::~Engine() { endwin(); }

void Engine::run() {
  while (state != ENGINE_EXIT) {
    state = actionTable[state]();
  }
}

void Engine::colors() {
  if (has_colors()) {
    start_color();
    if (blackBG) {
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      init_pair(2, 230, COLOR_BLACK);
      init_pair(3, 12, COLOR_BLACK);
      init_pair(4, 8, COLOR_BLACK);
      init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
      init_pair(6, 22, COLOR_BLACK);
      init_pair(7, 73, COLOR_BLACK);
    } else {
      init_pair(1, COLOR_YELLOW, COLOR_GREEN);
      init_pair(2, COLOR_YELLOW, 230);
      init_pair(3, COLOR_CYAN, 12);
      init_pair(4, COLOR_BLACK, 8);
      init_pair(5, COLOR_RED, COLOR_MAGENTA);
      init_pair(6, COLOR_YELLOW, 22);
      init_pair(7, COLOR_YELLOW, 73);
    }
  }
}