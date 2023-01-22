/**
 * @file skfantasy.h
 * @brief Game's main module
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
/**
 * @brief Both width and height of the level
 */
#define LEVEL_SIZE   128
/**
 * @brief Number of entities
 */
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
 * Represents a level of the world, with both visual and logic grids.
 */
struct level
{
  int visual[LEVEL_SIZE][LEVEL_SIZE];
  bool logic[LEVEL_SIZE][LEVEL_SIZE];
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
/**
 * @brief Generate a wilderness level
 * @param level The level
 */
void level_gen_wild(struct level *level);
/**
 * @brief Render the level
 * @param level The level
 */
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

