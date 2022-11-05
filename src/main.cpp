#include "game/game.h"
#include "view/colors.h"
#include "view/draw.h"

int main() {
  view::draw::setup();

  if (!view::colors::setup()) {
    view::draw::close();
    printf("Your terminal does not support color\n");
    return -1;
  }

  Game game;

  game.gameLoop();
  game.close();

  return 0;
}
