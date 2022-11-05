#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>

#include "position.h"

enum TileType : int { TILE_GRASS, TILE_SAND, TILE_WATER, TILE_MOUNTAIN };

class TileChunk {
public:
    TileChunk(int y, int x);
    ~TileChunk();

    int tileAt(int y, int x);

private:
    int getTileType(float elevation);

    int size = 32;
    std::vector<std::vector<int>> tiles;
};

class TileLayer {
public:
  TileLayer();
  ~TileLayer();

  Position generate();
  int tileAt(int y, int x);
  TileChunk chunkAt(int y, int x);
  bool inBounds(int y, int x);
  bool walkable(int y, int x);

 private:
  int chunksAround = 16;

  std::map<std::pair<int, int>, TileChunk> chunks;
};

#endif
