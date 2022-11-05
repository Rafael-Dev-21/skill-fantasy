#ifndef SK_VIEW_H
#define SK_VIEW_H

#ifdef __cplusplus
extern "C" {
#endif
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(MINGW32)
#include <curses.h>
#else
#include <ncurses.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
