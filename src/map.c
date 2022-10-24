#include <skfantasy.h>
#include <math.h>
 
Tile **genTerrain(void) {
  Tile **tiles = calloc(MAP_HEIGHT, sizeof(Tile *));
  for (int y = 0; y < MAP_HEIGHT; y++) {
    tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));
    for (int x = 0; x < MAP_WIDTH; x++) {
      float nx = x / (float)CHUNK_SIZE - 0.5f, ny = y / (float)CHUNK_SIZE - 0.5f;
      
      float e = (float)pow(fbm(nx, ny, 1, 3), 2);

      if (e < .1) {
        tiles[y][x].ch = '~';
        tiles[y][x].color = WATER_PAIR;
      } else if (e < .2) {
        tiles[y][x].ch = '~';
        tiles[y][x].color = SAND_PAIR;
      } else if (e < .5) {
        tiles[y][x].ch = ',';
        tiles[y][x].color = GRASS_PAIR;
      } else {
        tiles[y][x].ch = '^';
        tiles[y][x].color = MOUNTAIN_PAIR;
      }

      tiles[y][x].walkable = true;

      if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1) {
        tiles[y][x].walkable = false;
      }
    }
  }

  return tiles;
}

void freeMap(void) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    free(map[y]);
  }
  free(map);
}
