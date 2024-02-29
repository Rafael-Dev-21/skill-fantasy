#pragma once

#include <map>
#include <utility>
#include <vector>
#include <string>

#include <chrono>

#include "geom.hpp"
#include "noise.hpp"

enum class TileType { GRASS, WATER, SAND, STONE };

enum class Biome { DESERT, PLAINS, FOREST, TUNDRA };

class Tile {
public:
	Tile();
	~Tile();

	TileType getType();
	Biome getBiome();
	bool isVisible();
  
	void setType(TileType type);
	void setBiome(Biome biome);
	void setVisible(bool visible);

private:
	TileType type;
	Biome biome;
	bool visible;
};

class Chunk {
public:
	Chunk();
	~Chunk();

	void update(float dt);
	void generate(Noise const& noise);

	Tile& getTile(int x, int y) const;
	bool isLoaded();
	bool isVisible();

	static const int CHUNK_SIZE = 16;
private:
	int x;
	int y;
	bool loaded{false};
	bool visible{false};
	Tile * * tiles;
};

struct WorldParams {
  int width = 44000;
  int height = 44000;
  int chunkRadius = 2;
  unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
  int maxAltitude = 32;
  int minAltitude = 5;
  int limitAltitude = 64;
  int seaLevel = 10;
  float poles = 0.8f;
  float equator = 0.2f;
};

class World {
 public:
  World(WorldParams params = {});

  Tile const& tileAt(int x, int y);
  Chunk const& chunkAt(int x, int y);

  IPoint getSpawn();

  bool inBounds(int x, int y);

  bool isSpawnSet();
  
  int getWidth();
  
  int getHeight();

  void checkChunks(IPoint point);

 private:
  void genInitial();
  TileType getTile(float e, Biome b);
  Biome getBiome(float m, float t);

  std::unordered_map<std::pair<int, int>, Chunk> chunks;
  
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
