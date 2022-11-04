#include "map.h"
#include "colors.h"
#include "noise.h"
#include <cmath>

TileLayer::TileLayer(int width, int height) : width(width), height(height) {}
TileLayer::~TileLayer() = default;

int TileLayer::getTileType(float elevation) {
  if (elevation < .1)
    return TILE_WATER;
  else if (elevation < .2)
    return TILE_SAND;
  else if (elevation < .5)
    return TILE_GRASS;
  else
    return TILE_MOUNTAIN;
}

Position TileLayer::generate() {
  Position startPos(0, 0);

  int player = 0;

  for (int y = 0; y < height; y++) {
    tiles.push_back(std::vector<int>());
    for (int x = 0; x < width; x++) {
      float nx = x / 32.0 - 0.5;
      float ny = y / 32.0 - 0.5;

      float e = std::pow(noise::fbm(nx, ny, 1, 3) * 1.2, 2.75);

      int type = getTileType(e);

      if (type == TILE_GRASS && player == 0) {
        startPos.y = y;
        startPos.x = x;
        player = 1;
      }

      tiles.at(y).push_back(type);
    }
  }

  return startPos;
}

int TileLayer::tileAt(int y, int x) { return tiles.at(y).at(x); }

bool TileLayer::inBounds(int y, int x) {
  return (y >= 0 && y < height && x >= 0 && x < width);
}

bool TileLayer::walkable(int y, int x) {
  if (!inBounds(y, x))
    return false;
  if (tiles.at(y).at(x) == TILE_MOUNTAIN)
    return false;
  return true;
}
