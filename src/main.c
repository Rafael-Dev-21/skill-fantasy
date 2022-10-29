#include <colors.h>
#include <game.h>
#include <draw.h>
#include <map.h>

int main(void) {
  struct game game;
  draw_setup();

  if (setup_colors() == false) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }

  setup_game(&game);

  game_loop(&game);

  close_game(&game);

  return 0;
}
