#include "colors.h"
#include "draw.h"
#include "game.h"
#include "map.h"

int main(void) {
  draw::setup();

  if (!setup_colors()) {
    draw::close();
    printf("Your terminal does not support color\n");
    return -1;
  }

  Game game;

  game.gameLoop();
  game.close();

  return 0;
}
