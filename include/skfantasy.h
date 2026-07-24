#ifndef SKFANTASY_H
#define SKFANTASY_H

/************
 * INCLUDES *
 ************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(_WIN32) || defined(__MINGW__)
#include <curses.h>
#else
#include <ncursesw/ncurses.h>
#endif

#include "privdefs.h"

#endif
