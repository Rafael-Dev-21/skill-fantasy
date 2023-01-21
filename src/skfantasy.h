/**
 * @file skfantasy.h
 * @brief The header of the main module of the game
 */

#ifndef SKFANTASY_H
#define SKFANTASY_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef USE_NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif

/****************************
*   DEFINES
*****************************/
#define MAP_SIZE     128
#define ENTITY_COUNT 128

/****************************
*   ENUMS
*****************************/
/**
 * @brief Color pairs
 */
enum {
  PAIR_GRASS = 1,
  PAIR_MUD,
  PAIR_COUNT
};

/****************************
*   STRUCTS
*****************************/
/**
 * @brief Represents a location
 */
struct loc
{
  int x;
  int y;
};

/**
 * @brief Represents a level
 */
struct level
{
  int visual[MAP_SIZE][MAP_SIZE];
  bool logic[MAP_SIZE][MAP_SIZE];
};

/**
 * @brief Represents a entity
 */
struct entity
{
  struct loc pos;
  char sprite;
  int appaerance;
};

/****************************
*   PROTOTYPES
*****************************/
/* level */
void level_gen_wild(struct level *level);
void level_render(struct level *level);

/* game */
bool game_init(void);
void game_loop(void);
void game_exit(void);

/* colors */
bool colors_init(void);

/* externs */
extern struct level level;
extern struct entity player;

#endif

