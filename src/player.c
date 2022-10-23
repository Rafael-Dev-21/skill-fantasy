#include <skfantasy.h>

Entity *createPlayer(Position start_pos) {
  Entity *newPlayer = calloc(1, sizeof(Entity));

  newPlayer->pos.y = start_pos.y;
  newPlayer->pos.x = start_pos.x;
  newPlayer->ch = '@';
  newPlayer->color = PLAYER_PAIR;

  return newPlayer;
}

void handleInput(int input) {
  Position newPos = {player->pos.y, player->pos.x};

  switch (input) {
  case 'k':
    newPos.y--;
    break;
  case 'j':
    newPos.y++;
    break;
  case 'h':
    newPos.x--;
    break;
  case 'l':
    newPos.x++;
    break;
  default:
    break;
  }

  movePlayer(newPos);
}

void movePlayer(Position next) {
  if (map[next.y][next.x].walkable) {
    player->pos.y = next.y;
    player->pos.x = next.x;
  }
}
