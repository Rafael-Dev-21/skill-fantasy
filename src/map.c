#include <skfantasy.h>
#include <colors.h>
#include <map.h>
#include <math.h>
 
Tile **genTerrain(void) {
  Tile **tiles = calloc(MAP_HEIGHT, sizeof(Tile *));

  for (int y = 0; y < MAP_HEIGHT; y++) {
    tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));
    for (int x = 0; x < MAP_WIDTH; x++) {
      float nx = x / 32.0f - 0.5f, ny = y / 32.0f - 0.5f;
      
      float e = pow(fbm(nx, ny, 1, 3) * 1.2, 2.75);

      if (e < .1) {
        tiles[y][x].ch = '~';
        tiles[y][x].color = SKPAIR_WATER;
      } else if (e < .2) {
        tiles[y][x].ch = '~';
        tiles[y][x].color = SKPAIR_SAND;
      } else if (e < .5) {
        tiles[y][x].ch = ',';
        tiles[y][x].color = SKPAIR_GRASS;
      } else {
        tiles[y][x].ch = '^';
        tiles[y][x].color = SKPAIR_MOUNTAIN;
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

enum tile_type get_tile(float elevation)
{
	if (elevation < .1)
		return TILE_WATER;
	else if (elevation < .2)
		return TILE_SAND;
	else if (elevation < .5)
		return TILE_GRASS;
	else
		return TILE_MOUNTAIN;
}
