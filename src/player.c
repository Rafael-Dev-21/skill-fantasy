#include <skfantasy.h>

struct entity *createPlayer(struct position start_pos) {
  struct entity *new_player = calloc(1, sizeof(*new_player));

  new_player->pos.y = start_pos.y;
  new_player->pos.x = start_pos.x;
  new_player->ch = '@';
  new_player->color = PLAYER_PAIR;

  return new_player;
}

void handleInput(int input) {
  struct position new_pos = {player->pos.y, player->pos.x};

  switch (input) {
  case 'k':
    new_pos.y--;
    break;
  case 'j':
    new_pos.y++;
    break;
  case 'h':
    new_pos.x--;
    break;
  case 'l':
    new_pos.x++;
    break;
  default:
    break;
  }

  movePlayer(new_pos);
}

void movePlayer(struct position next) {
  if (map[next.y][next.x].walkable) {
    player->pos.y = next.y;
    player->pos.x = next.x;
  }
}
