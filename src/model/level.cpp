#include "model/level.hpp"

#include <cmath>

#include "util/math.hpp"
#include "util/noise.hpp"

Tile::Tile(TileType type, Biome biome) : type(type), biome(biome) {
  switch (type) {
    case TileType::GRASS:
      sprite = ',';
      switch (biome) {
        case Biome::FOREST:
          colors = 6;
          break;
        case Biome::TUNDRA:
          colors = 7;
          break;
        default:
          colors = 1;
      }
      break;
    case TileType::SAND:
      sprite = '~';
      colors = 2;
      break;
    case TileType::WATER:
      sprite = '~';
      colors = 3;
      break;
    case TileType::STONE:
      sprite = '.';
      colors = 4;
  }
}

World::World(WorldParams params):
  worldParams(params),
  noise(Simplex(params.seed))
{

  fbmParams.amplitude = 0.5;
  fbmParams.frequency = 0.01;
  fbmParams.octaves = 10;

  genInitial();
}

Tile World::tileAt(int x, int y) { return tiles[std::pair<int, int>(x, y)]; }

IPoint World::getSpawn() { return spawn; }

bool World::inBounds(int x, int y) {
  return x >= 0 && y >= 0 && worldParams.width > x && worldParams.height > y;
}

bool World::isSpawnSet() { return spawnSet; }

int World::getWidth() {
  return worldParams.width;
}

int World::getHeight() {
  return worldParams.height;
}

void World::checkChunks(IPoint point) {
  if (inBounds(point.x, point.y)) {
    int x = point.x / worldParams.chunkSize;
    int y = point.y / worldParams.chunkSize;

    for (int j = y - worldParams.chunkRadius; j < y + worldParams.chunkRadius; j++) {
      for (int i = x - worldParams.chunkRadius; i < x + worldParams.chunkRadius; i++) {
        if (inBounds(i * worldParams.chunkSize, j * worldParams.chunkSize)) {
          genChunk(i, j);
        }
      }
    }
  }
}

void World::genInitial() {
  int x = worldParams.width / (worldParams.chunkSize * 2);
  int y = worldParams.height / (worldParams.chunkSize * 2);
  
  genChunk(x, y);

  int offx = 1;
  int offy = 1;

  while (!spawnSet) {
    for (int j = -offy; j < offy; j += offy * 2 - 1) {
      for (int i = -offx; i < offx; i += offx * 2 - 1) {
        if (inBounds(i * worldParams.chunkSize, j * worldParams.chunkSize)) {
          genChunk(x + i, y + j);
        }
      }
    }
    offx++;
    offy++;
  }

  checkChunks(spawn);
}

void World::genChunk(int chunkX, int chunkY) {
  if (chunkVisited[{chunkX, chunkY}]) return;

  chunkVisited[{chunkX, chunkY}] = true;

  int startX = chunkX * worldParams.chunkSize;
  int startY = chunkY * worldParams.chunkSize;
  int endX = (chunkX + 1) * worldParams.chunkSize;
  int endY = (chunkY + 1) * worldParams.chunkSize;

  for (int y = startY; y < endY; y++) {
    for (int x = startX; x < endX; x++) {
      float e = noise.fbm(x + noise.fbm(x, y, fbmParams), y + noise.fbm(x, y, fbmParams), fbmParams);
      float m = noise.fbm(x + 1000, y, fbmParams);
      float t = e*e + worldParams.poles + (worldParams.equator-worldParams.poles) * std::sin(3.14159 * ((float)y / worldParams.height));

      auto biome = getBiome(m, t);
      auto type = getTile(e * worldParams.maxAltitude, biome);
      
      tiles[{x, y}] = Tile(type, biome);

      if (type == TileType::STONE && e >= 0.98) {
        auto fix = new FixedObject{};
        
        fix->name = "Stone Wall";
        fix->sprite = '#';
        fix->colors = 4;
        
        tiles[{x, y}].fixedObject = fix;
      }
      
      if (biome == Biome::FOREST && type == TileType::GRASS && Math::hash(x, y) > 0.75) {
        auto fix = new FixedObject{};
        
        fix->name = "Oak Tree";
        fix->sprite = 'T';
        fix->colors = 6;
        
        tiles[{x, y}].fixedObject = fix;
      }

      if (type != TileType::WATER && !(tiles[{x, y}].fixedObject && tiles[{x, y}].fixedObject->block) && !spawnSet) {
        spawn.x = x;
        spawn.y = y;
        spawnSet = true;
      }
    }
  }
}

TileType World::getTile(float e, Biome b) {
  int dHeight = worldParams.maxAltitude - worldParams.seaLevel;
  
  auto lv = [dHeight, this](float dt){
    return worldParams.seaLevel + dHeight * dt;
  };
  
  if (e < lv(0)) {
    return TileType::WATER;
  } else if (e < lv(3.0/11.0)) {
    return TileType::SAND;
  } else if (e < lv(9.0/11.0)) {
    if (b == Biome::DESERT) {
      return TileType::SAND;
    } else {
      return TileType::GRASS;
    }
  } else {
    return TileType::STONE;
  }
}

Biome World::getBiome(float m, float e) {
  if (e > 0.8) {
    return Biome::TUNDRA;
  }

  if (e > 0.6) {
    if (m < 0.33) {
      return Biome::DESERT;
    }
    if (m < 0.66) {
      return Biome::PLAINS;
    }
    
    return Biome::FOREST;
  }
  
  if (e > 0.3) {
    if (m < 0.16) {
      return Biome::DESERT;
    }
    if (m < 0.5) {
      return Biome::PLAINS;
    }
    return Biome::FOREST;
  }

  return Biome::FOREST;
}