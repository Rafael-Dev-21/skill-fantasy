#ifndef _COMMONS_H_
#define _COMMONS_H_

#include <string>

#define VERSION "v.0-alpha"

#ifdef _WIN32

#include <curses.h>

#endif

#ifdef __linux__

extern "C" {
#include <ncurses.h>
}

#endif

#endif
