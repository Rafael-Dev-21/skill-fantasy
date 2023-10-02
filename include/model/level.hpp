#pragma once

#include <map>
#include <utility>

#include <ctime>

#include "util/geom.hpp"
#include "util/noise.hpp"
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

struct WorldParams {
  int width = 44000;
  int height = 44000;
  int chunkSize = 32;
  int chunkRadius = 2;
  int seed = time(nullptr);
  int maxAltitude = 32;
  int minAltitude = 5;
  int limitAltitude = 64;
  int seaLevel = 10;
  float poles = 0.8;
  float equator = 0.2;
};

class World {
 public:
  World(WorldParams params = {});

  Tile tileAt(int x, int y);

  IPoint getSpawn();

  bool inBounds(int x, int y);

  bool isSpawnSet();
  
  int getWidth();
  
  int getHeight();

  void checkChunks(IPoint point);

 private:
  void genInitial();
  void genChunk(int chunkX, int chunkY);
  TileType getTile(float e, Biome b);
  Biome getBiome(float m, float t);

  std::map<std::pair<int, int>, Tile> tiles;
  std::map<std::pair<int, int>, bool> chunkVisited;
  
  WorldParams worldParams;

  bool spawnSet = false;

  IPoint spawn;
  Simplex noise;
  FBMParams fbmParams;
};

class WorldBuilder {
  public:
  WorldBuilder();
  
  void setWidth(int width);
  void setHeight(int height);
  void setChunkSize(int chunkSize);
  void setChunkRadius(int chunkRadius);
  void setSeed(int seed);
  void setMaxAltitude(int maxAltitude);
  void setMinAltitude(int minAltitude);
  void setLimitAltitude(int limitAltitude);
  void setSeaLevel(int seaLevel);
  void setPoles(float poles);
  void setEquator(float equator);
  
  World * build();
  
  private:
  WorldParams params;
};