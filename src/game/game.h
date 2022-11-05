#ifndef GAME_H
#define GAME_H

#include <array>

#include "entity.h"
#include "map.h"

struct Game {
 public:
  Game();
  ~Game();

  void update();
  void nextInput();
  void gameLoop();
  void close();

  Entity player = Entity({0, 0});
  std::array<TileLayer, 2> layers{{{128, 128}, {128, 128}}};

  int currentLayer;
  int currentInput;
};

#endif
