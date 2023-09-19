#include "level.hpp"

#include <curses.h>

#include <cmath>

#include "math.hpp"
#include "noise.hpp"

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

Level::Level(int chunkSize, int chunkRadius)
    : chunkSize(chunkSize), chunkRadius(chunkRadius) {
  if (chunkSize < 2 || chunkSize % 2 != 0) {
    chunkSize = 32;
  }

  if (chunkRadius < 1) {
    chunkRadius = 2;
  }

  heightParams.amplitude = 8;
  heightParams.frequency = 0.01;
  heightParams.octaves = 10;

  biomeParams.amplitude = 0.5;
  biomeParams.frequency = 0.01;
  biomeParams.octaves = 10;

  genInitial();
}

Tile Level::tileAt(int x, int y) { return tiles[std::pair<int, int>(x, y)]; }

void Level::render(IVector cameraOrigin) {
  for (int y = 0; y < LINES; y++) {
    for (int x = 0; x < COLS; x++) {
      int mapx = x + cameraOrigin.x;
      int mapy = y + cameraOrigin.y;

      auto tile = tileAt(mapx, mapy);
      
      int graphic = ' ';
      if (tile.fixedObject) {
        graphic = tile.fixedObject->sprite | COLOR_PAIR(tile.fixedObject->colors);
      } else {
        graphic = tile.sprite | COLOR_PAIR(tile.colors);
      }
      mvaddch(y, x, graphic);
    }
  }
}

IPoint Level::getSpawn() { return spawn; }

bool Level::isSpawnSet() { return spawnSet; }

void Level::checkChunks(IPoint point) {
  int x = point.x / chunkSize;
  int y = point.y / chunkSize;

  for (int j = y - chunkRadius; j < y + chunkRadius; j++) {
    for (int i = x - chunkRadius; i < x + chunkRadius; i++) {
      genChunk(i, j);
    }
  }
}

void Level::genInitial() {
  genChunk(0, 0);

  int x = 1;
  int y = 1;

  while (!spawnSet) {
    for (int j = -y; j < y; j += y * 2 - 1) {
      for (int i = -x; i < x; i += x * 2 - 1) {
        genChunk(i, j);
      }
    }
    x++;
    y++;
  }

  checkChunks(spawn);
}

void Level::genChunk(int chunkX, int chunkY) {
  if (chunkVisited[{chunkX, chunkY}]) return;

  chunkVisited[{chunkX, chunkY}] = true;

  int startX = chunkX * chunkSize;
  int startY = chunkY * chunkSize;
  int endX = (chunkX + 1) * chunkSize;
  int endY = (chunkY + 1) * chunkSize;

  for (int y = startY; y < endY; y++) {
    for (int x = startX; x < endX; x++) {
      float e = fmax(fmin(round(noise.fbm(x, y, heightParams)), 16), 0);
      float m = noise.fbm(x + 1000, y, biomeParams);
      float t = noise.fbm(x, y + 1000, biomeParams);

      auto biome = getBiome(m, t);
      auto type = getTile(e, biome);
      
      tiles[{x, y}] = Tile(type, biome);

      if (type == TileType::STONE && e == 16) {
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

TileType Level::getTile(float e, Biome b) {
  if (e < 6) {
    return TileType::WATER;
  } else if (e < 9) {
    return TileType::SAND;
  } else if (e < 14) {
    if (b == Biome::DESERT) {
      return TileType::SAND;
    } else {
      return TileType::GRASS;
    }
  } else {
    return TileType::STONE;
  }
}

Biome Level::getBiome(float m, float t) {
  if (t > 0.5) {
    if (m < 0.3) {
      return Biome::DESERT;
    }

    if (m < 0.5) {
      return Biome::PLAINS;
    }

    return Biome::FOREST;
  }

  if (t > 0.3) {
    if (m < 0.2) {
      return Biome::DESERT;
    }
    return Biome::PLAINS;
  }

  if (m < 0.1) {
    return Biome::DESERT;
  }

  if (m < 0.2) {
    return Biome::PLAINS;
  }

  return Biome::TUNDRA;
}