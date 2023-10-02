#include <chrono>
#ifdef __MINGW32__
#include "mingw.thread.h"
#else
#include <thread>
#endif

#include "controller/curses.hpp"
#include "model/engine.hpp"
#include "view/curses.hpp"
#include "util/events.hpp"

int main(void) {
  EventSystem evSystem;
  Engine game(evSystem);
  CursesController control(game, evSystem);
  CursesView view(game, evSystem);

  std::thread loop([&game]() {
    game.run();
  });
  
  loop.join();

  return 0;
}
