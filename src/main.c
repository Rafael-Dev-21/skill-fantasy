#include <skfantasy.h>
#include <colors.h>
#include <game.h>

const int MAP_WIDTH = 128;
const int MAP_HEIGHT = 128;
const int VIEW_WIDTH = 50;
const int VIEW_HEIGHT = 20;
const int CHUNK_SIZE = 16;

struct entity *player;
Tile **map;

int main(void) {
  struct game game;
  cursesSetup();

  if (setup_colors() == false) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }

  setup_game(&game);

  player = game.player;
  map = genTerrain();

  gameLoop();

  closeGame();

  return 0;
}
