#ifndef SKFANTASY_H
#define SKFANTASY_H

#include <ncurses.h>
#include <stdlib.h>

// defines
#define GRASS_PAIR    1
#define EMPTY_PAIR    1
#define SAND_PAIR     2
#define WATER_PAIR    3
#define MOUNTAIN_PAIR 4
#define PLAYER_PAIR   5

// structures
typedef struct {
  int y;
  int x;
} Position;

typedef struct {
  char ch;
  int color;
  bool walkable;
} Tile;

typedef struct {
  Position pos;
  char ch;
  int color;
} Entity;

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
Entity *createPlayer(Position start_pos);
void handleInput(int input);
void movePlayer(Position next);

// drawing
void drawEntity(Entity *entity);
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
extern Entity *player;

#endif
