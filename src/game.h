#ifndef GAME_H_
#define GAME_H_

#include <stdint.h>
#include <stddef.h>

typedef struct {
  uint32_t fps;

  uint32_t *display;
  size_t display_width;
  size_t display_height;
} Game;

Game Game_init(void);
void Game_update(void);
void Game_mouseMove(int x, int y);

#endif // GAME_H_
