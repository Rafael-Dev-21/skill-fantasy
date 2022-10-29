#include <skfantasy.h>
#include <colors.h>
#include <game.h>
#include <map.h>

const int VIEW_WIDTH = 50;
const int VIEW_HEIGHT = 20;
const int CHUNK_SIZE = 16;

struct entity *player;
struct tile **map;

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
  map = game.map;

  gameLoop();

  closeGame();

  return 0;
}
