#include "skfantasy.h"

bool mob_move(mob_t *mob, map_t map, direction_t dir, int amount)
{
  int dx = 0, dy = 0;
  switch (dir) {
  case DNORTH:
    dy=-amount;
    break;
  case DSOUTH:
    dy= amount;
    break;
  case DWEST:
    dx=-amount;
    break;
  case DEAST:
    dx= amount;
    break;
  default:
    return false;
  }
  int nx = mob->pos.x + dx;  
  int ny = mob->pos.y + dy;  
  if (nx < 0 || ny < 0 || nx >= MAP_WIDTH || ny >= MAP_HEIGHT || map[ny][nx].walkable == false) {  
    return false;  
  }  
  mob->pos.x = nx;  
  mob->pos.y = ny;  
  return true;
}
