#include <skfantasy.h>

#define offsetY (player->pos.y - VIEW_HEIGHT / 2)
#define offsetX (player->pos.x - VIEW_WIDTH / 2)

void drawEntity(Entity *entity) {
  mvaddch(entity->pos.y + offsetY, entity->pos.x + offsetX,
          entity->ch | COLOR_PAIR(entity->color));
}

void drawPlayer(void) {
  mvaddch(VIEW_HEIGHT / 2, VIEW_WIDTH / 2,
          player->ch | COLOR_PAIR(player->color));
}

void drawMap(void) {
  int endY = player->pos.y + VIEW_HEIGHT / 2;
  int endX = player->pos.x + VIEW_WIDTH / 2;

  int row = 0;
  for (int y = offsetY; y < endY; y++) {
    int col = 0;
    for (int x = offsetX; x < endX; x++) {
      if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH) {
        mvaddch(row, col, ' ');
      } else {
        mvaddch(row, col, map[y][x].ch | COLOR_PAIR(map[y][x].color));
      }
      col++;
    }
    row++;
  }
}

void drawEverything(void) {
  clear();
  drawMap();
  drawPlayer();
}
