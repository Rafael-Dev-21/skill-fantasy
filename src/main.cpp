#include <chrono>
#include <thread>

#include "engine.hpp"
#include "events.hpp"

int main(void) {
  EventSystem evSystem;
  Engine game(evSystem);

  std::thread loop([&game]() {
    game.run();
  });
  
  loop.join();

  return 0;
}
