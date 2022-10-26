#include <skfantasy.h>

const int MAP_WIDTH = 4096;
const int MAP_HEIGHT = 4096;
const int VIEW_WIDTH = 50;
const int VIEW_HEIGHT = 20;
const int CHUNK_SIZE = 16;

Entity *player;
Tile **map;

int main(void) {
  cursesSetup();

  if (has_colors() == false) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }
  start_color();
  init_pair(GRASS_PAIR, COLOR_YELLOW, COLOR_GREEN);
  init_pair(SAND_PAIR, COLOR_YELLOW, COLOR_WHITE);
  init_pair(WATER_PAIR, COLOR_CYAN, COLOR_BLUE);
  init_pair(MOUNTAIN_PAIR, COLOR_BLACK, COLOR_WHITE);
  init_pair(PLAYER_PAIR, COLOR_RED, COLOR_MAGENTA);

  Position start_pos = {10, 20};
  player = createPlayer(start_pos);
  map = genTerrain();

  gameLoop();

  closeGame();

  return 0;
}
