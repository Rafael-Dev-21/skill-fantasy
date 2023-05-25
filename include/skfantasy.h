#pragma once

/**
 * skfantasy -- ASCII survival game
 * Copyright (C) 2023 Rafael-Dev-21
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * Constants
 */

#define FPS 30
#define NSEC 1000000000
#define FRAMES (NSEC / FPS)

#define ESC 27

/**
 * Typedefs
 */

typedef enum {
	TILE_GRASS
} tile_t;

typedef struct {
	int y;
	int x;
} position_t;

typedef struct {
	position_t pos;
	int width;
	int height;
	unsigned length;
	tile_t tiles[];
} level_t;

/*************************
 * Function Declarations *
 *************************/

/**
 * curses
 */
void initCurses(void);
void endCurses(void);

/**
 * Level
 */
level_t *newLevel(position_t, int, int);
void drawLevel(level_t *);
void freeLevel(level_t *);
