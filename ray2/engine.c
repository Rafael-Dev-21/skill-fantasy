#include "skfantasy.h"

#include <ctype.h>
#include <curses.h>

int game_start(mob_t *player, map_t map, int input)
{
  draw_start_menu();
  if (input == 's') {
    player->pos.x = MAP_WIDTH/2;
    player->pos.y = MAP_HEIGHT/2;
    map_gen(map);
    map_update_visible(map, player->pos, FOV_RADIUS);
    return 1;
  }
  return 0;
}

int game_play(mob_t *player, map_t map, int input)
{
  direction_t d;
  bool isMove = false;
  switch (tolower(input)) {
  case 'h':
    d = DWEST;
    isMove = true;
    break;
  case 'j':
    d = DSOUTH;
    isMove = true;
    break;
  case 'k':
    d = DNORTH;
    isMove = true;
    break;
  case 'l':
    d = DEAST;
    isMove = true;
    break;
  case ESC:
    return 0;
  }

  if (isMove) {  
    isMove = mob_move(player, map, d, 1);  
    if (isMove) {  
      map_update_visible(map, player->pos, FOV_RADIUS);  
    }  
  }  

  position_t eye = player->pos;  
  int offx = COLS/2;  
  int offy = (LINES-3)/2;  
  eye.x -= offx;  
  eye.y -= offy;  
  if (eye.x < 0) {  
    eye.x = 0;  
  }  
  if (eye.y < 0) {  
    eye.y = 0;  
  }  
  if (eye.x >= MAP_WIDTH-offx) {  
    eye.x = MAP_WIDTH-offx-1;  
  }  
  if (eye.y >= MAP_HEIGHT-offy) {  
    eye.y = MAP_HEIGHT-offy-1;  
  }  

  draw_map(map, eye);  
  draw_mob(player, eye);  
  return 1;
}
