#ifndef GAME_H
#define GAME_H

#include <array>
#include "colors.h"
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

  Entity player = Entity({0, 0}, '@', SKPAIR_PLAYER);
  std::array<TileLayer, 2> layers;

  int currentLayer;
  int currentInput;
};

#endif
