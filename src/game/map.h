#ifndef MAP_H
#define MAP_H

#include <vector>

#include "position.h"

enum TileType : int { TILE_GRASS, TILE_SAND, TILE_WATER, TILE_MOUNTAIN };

struct TileLayer {
  TileLayer(int width, int height);
  ~TileLayer();

  Position generate();
  int tileAt(int y, int x);
  bool inBounds(int y, int x);
  bool walkable(int y, int x);

 private:
  int getTileType(float elevation);

  int width;
  int height;
  std::vector<std::vector<int>> tiles;
};

#endif
