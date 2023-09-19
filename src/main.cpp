#include "engine.hpp"

Level *level = nullptr;
Entity *player = nullptr;

int main(void) {
  Engine game(false);

  game.run();

  delete level;
  delete player;

  return 0;
}
