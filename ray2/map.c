#include <stdlib.h>
#include <math.h>
#include "skfantasy.h"
#include "noise/noise.h"
#include "noise/mymath.h"

void map_gen(map_t map)
{
  FBMParams params = default_fbm;
  params.noisefn = simplex2d;

  for (int i = 0; i < MAP_HEIGHT; i++) {  
    for (int j = 0; j < MAP_WIDTH; j++) {  
      float nx = j / 16.0 - 0.5;  
      float ny = i / 16.0 - 0.5;  

      float n = fbm2d(nx, ny, params)*0.5+0.5;
      double chance = hash_posf(j, i);

      tile_t *tile = &map[i][j];  
      if (n > 0.7 && chance > 0.75) {  
        int type = rand()%2;  
        *tile = (tile_t){type?'T':'0', 0, false, false, false};  
      } else if (n > 0.6 && chance > 0.375) {  
        int type = rand()%2;  
        *tile = (tile_t){type?'/':'o', 0, true, false, true};  
      } else if (n>0.6 && chance > 0.75) {  
        *tile = (tile_t){'*', 0, true, false, true};  
      } else {  
        *tile = (tile_t){'.', 0, true, false, true};  
      }  
    }  
  }
}

void map_update_visible(map_t map, position_t center, int radius)
{
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      map[i][j].visible = false;
    }
  }
  //float one_cycle = M_PI/(FOV_ANGLES/2.0);
  map[center.y][center.x].visible = true;
  for (int i = 0; i < MAP_WIDTH; i++) {  
//    double angle = i * one_cycle;  
    int angle = (1024 * i / MAP_WIDTH - 512);
    map_cast_light(map, center, angle, radius);  
  }
}

void map_cast_light(map_t map, position_t center, int angle, int radius)
{
  int dx = angle;
  int dy = (angle + 256);
  if (dy > 512) {
    dy = -512 + (dy - 512);
  }

  if (dx > 256) {
    dx = 512 - dx;
  }
  if (dx < -256) {
    dx = -512 - dx;
  }
  if (dy > 256) {
    dy = 512 - dy;
  }
  if (dy < -256) {
    dy = -512 - dy;
  }

  int mx = center.x;
  int my = center.y;

  int mr = radius * radius;

  long long int sdx, sdy;

  int ddx = !dx ? 0xFFFF : abs(0xFFFF/dx);
  int ddy = !dy ? 0xFFFF : abs(0xFFFF/dy);

  int sx, sy;
  sdx = 0, sdy = 0;
  sx = dx == 0 ? 0 : (dx < 0 ? -1 : 1);
  sy = dy == 0 ? 0 : (dy < 0 ? -1 : 1);

  int pwd = 0;

  while (pwd < mr) {
    {
      int mdx = mx - center.x;
      int mdy = my - center.y;
      pwd = (mdx * mdx + mdy * mdy);
    }
    if (sdx < sdy) {
      sdx += ddx;
      mx += sx;
    } else {
      sdy += ddy;
      my += sy;
    }
    if (mx < 0 || my < 0 || MAP_WIDTH < mx || MAP_HEIGHT < my) {
      break;
    }
    map[my][mx].visible = true;
    if (map[my][mx].transparent == false) {
      break;
    }
  }

  /*
  const double RSQUARED = radius * radius;
  while ((dx * dx + dy * dy) < RSQUARED) {
    int cx = center.x + dx;
    int cy = center.y + dy;
    if (cx < 0 || cy < 0 || cx >= MAP_WIDTH || cy >= MAP_HEIGHT) {
      break;
    }
    map[cy][cx].visible = true;
    if (map[cy][cx].transparent == false) {
      break;
    }
    dx += cos(angle)*0.1;
    dy += sin(angle)*0.1;
  }
  */

}
