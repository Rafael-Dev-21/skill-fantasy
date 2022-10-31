#ifndef SK_COMMON_H
#define SK_COMMON_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(MINGW32)
  #include <curses.h>
#else
  #include <ncurses.h>
#endif
#include <stdlib.h>
#include <stdbool.h>

#endif
