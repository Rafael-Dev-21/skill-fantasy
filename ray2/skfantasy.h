#ifndef SKFANTASY_H
#define SKFANTASY_H

#include <stdbool.h>

#define ESC 27
#define CTRL_KEY(k) ((k)&0x1f)

#define MAP_WIDTH 80
#define MAP_HEIGHT 80

#define FOV_RADIUS 8
#define FOV_ANGLES 512

typedef enum direction {
  DNORTH,
  DSOUTH,
  DWEST,
  DEAST
} direction_t;

typedef struct position {
  int x;
  int y;
} position_t;

typedef struct mob {
  position_t pos;
  int glyph;
  int color;
} mob_t;

typedef struct tile {
  int glyph;
  int color;
  bool walkable;
  bool visible;
  bool transparent;
} tile_t;

typedef tile_t map_t[MAP_HEIGHT][MAP_WIDTH];

/*
Curses
*/
void curses_init(void);
void curses_cleanup(void);


/*
Engine
*/
int game_start(mob_t *player, map_t map, int input);
int game_play(mob_t *player, map_t map, int input);


/*
Mob
*/
bool mob_move(mob_t *mob, map_t map, direction_t dir, int amount);


/*
Map
*/
void map_gen(map_t map);
void map_update_visible(map_t map, position_t center, int radius);
void map_cast_light(map_t map, position_t center, int angle, int radius);


/*
Draw
*/
void draw_start_menu(void);
void draw_mob(mob_t *mob, position_t eye);
void draw_map(map_t map, position_t eye);


#endif
