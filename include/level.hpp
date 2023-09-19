#pragma once

#include <map>
#include <utility>

#include "geom.hpp"
#include "noise.hpp"
#include "objects.hpp"

enum class TileType { GRASS, WATER, SAND, STONE };

enum class Biome { DESERT, PLAINS, FOREST, TUNDRA };

struct Tile {
  Tile(TileType type = TileType::GRASS, Biome biome = Biome::PLAINS);

  TileType type;
  Biome biome;
  int sprite;
  int colors;
  
  FixedObject *fixedObject = nullptr;
  LooseObject *looseObject = nullptr;
};

class Level {
 public:
  Level(int chunkSize = 32, int chunkRadius = 2);

  Tile tileAt(int x, int y);

  void render(IVector cameraOrigin);

  IPoint getSpawn();

  bool inBounds(int x, int y);

  bool isSpawnSet();

  void checkChunks(IPoint point);

 private:
  void genInitial();
  void genChunk(int chunkX, int chunkY);
  TileType getTile(float e, Biome b);
  Biome getBiome(float m, float t);

  std::map<std::pair<int, int>, Tile> tiles;
  std::map<std::pair<int, int>, bool> chunkVisited;
  int chunkSize;
  int chunkRadius;

  bool spawnSet = false;

  IPoint spawn;
  Simplex noise;
  FBMParams heightParams;
  FBMParams biomeParams;
};