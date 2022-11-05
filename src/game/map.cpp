#include "map.h"

#include <cmath>

#include "noise.h"

TileChunk::TileChunk(int y, int x) {
    for (int row = 0; row < size; row++) {
        tiles.push_back(std::vector<int>());
        for (int col = 0; col < size; col++) {
            float ny = (row / (float)size) - 0.5;
            float nx = (col / (float)size) - 0.5;
            float e = std::pow(noise::fbm(nx + std::abs(x), ny + std::abs(y), 1, 3, noise::noise2d) * 1.2, 2.75);
            int tile = getTileType(e);
            tiles.at(row).push_back(tile);
        }
    }
}

TileChunk::~TileChunk() = default;

int TileChunk::tileAt(int y, int x) {
    return tiles.at(std::abs(y)).at(std::abs(x));
}

int TileChunk::getTileType(float e) {
    if (e <  .1)
        return TILE_WATER;
    else if (e < .2)
        return TILE_SAND;
    else if (e < .5)
        return TILE_GRASS;
    else
     return TILE_MOUNTAIN;
}

TileLayer::TileLayer() {}
TileLayer::~TileLayer() = default;

Position TileLayer::generate() {
  Position startPos(20, 20);

  for (int y = -chunksAround; y <= chunksAround; y++) {
      for (int x = -chunksAround; x <= chunksAround; x++) {
          int chunkY = y + startPos.y / 32;
          int chunkX = x + startPos.x / 32;

          chunks.insert({ {chunkY, chunkX}, {chunkY, chunkX}});
      }
  }

  return startPos;
}

int TileLayer::tileAt(int y, int x) {
    return chunkAt(y / 32, x / 32).tileAt(y % 32, x % 32);
}
TileChunk TileLayer::chunkAt(int y, int x) {
    return chunks.at(std::make_pair(y, x));
}

bool TileLayer::inBounds(int y, int x) {
  int minLimit = -chunksAround * 32;
  int maxLimit = (chunksAround + 1) * 32;

  return y > minLimit && y < maxLimit && x > minLimit && x < maxLimit;
}

bool TileLayer::walkable(int y, int x) {
  if (!inBounds(y, x)) return false;
  if (tileAt(y, x) == TILE_MOUNTAIN) return false;
  return true;
}
