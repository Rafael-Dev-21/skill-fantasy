/**
 * @file main.c
 * @brief Main file of the game
 */

#include "skfantasy.h"

struct level level;
struct entity player;

int
main (void)
{
  if (!game_init())
    {
      game_exit();
      return EXIT_FAILURE;
    }

  game_loop();
  game_exit();

  return EXIT_SUCCESS;
}
