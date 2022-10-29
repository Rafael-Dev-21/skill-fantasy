#ifndef SKFANTASY_H
#define SKFANTASY_H

#include "common.h"

#include "position.h"
#include "entity.h"

// defines
#define GRASS_PAIR    1
#define EMPTY_PAIR    1
#define SAND_PAIR     2
#define WATER_PAIR    3
#define MOUNTAIN_PAIR 4
#define PLAYER_PAIR   5

// structures

typedef struct {
  char ch;
  int color;
  bool walkable;
} Tile;

// engine
void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

// math
float lerp(float x, float y, float s);
float smoothstep(float x, float y, float s);
float noise2(int x, int y);
float noise2d(float x, float y);
float fbm(float x, float y, float freq, int depth);

// map
Tile **genTerrain(void);
void freeMap(void);

// player
struct entity *createPlayer(struct position start_pos);
void handleInput(int input);
void movePlayer(struct position next);

// drawing
void drawEntity(struct entity *entity);
void drawPlayer(void);
void drawMap(void);
void drawEverything(void);

// externs
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;
extern const int VIEW_WIDTH;
extern const int VIEW_HEIGHT;
extern const int CHUNK_SIZE;

extern Tile **map;
extern struct entity *player;

#endif
