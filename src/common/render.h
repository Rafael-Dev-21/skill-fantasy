#pragma once

#include <stdint.h>
#include "util.h"
#include "surface.h"

#define DISPLAY_WIDTH  640
#define DISPLAY_HEIGHT 480

#ifdef SK_IS_ANDROID
#define BLACK   0xFF000000
#define CYAN    0xFFFFFF00
#define MAGENTA 0xFFFF00FF
#define YELLOW  0xFF00FFFF
#define WHITE   0xFFFFFFFF
#define BLUE    0xFFFF0000
#define RED     0xFF0000FF
#define GREEN   0xFF00FF00
#else
#define BLACK   0xFF000000
#define CYAN    0xFF00FFFF
#define MAGENTA 0xFFFF00FF
#define YELLOW  0xFFFFFF00
#define WHITE   0xFFFFFFFF
#define BLUE    0xFF0000FF
#define RED     0xFFFF0000
#define GREEN   0xFF00FF00
#endif

void clearDisplay(uint32_t color);
void fillCircle(int cx, int cy, int cr, uint32_t color);
void strokeCircle(int cx, int cy, int cr, uint32_t color);
void strokeLine(int x1, int y1, int x2, int y2, uint32_t color);
void fillTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint32_t color);
void strokeTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint32_t color);
void blitTriangle(int ax, int ay, int bx, int by, int cx, int cy, int tax, int tay, int tbx, int tby, int tcx, int tcy, const Surface * restrict s);

extern uint32_t display[DISPLAY_WIDTH*DISPLAY_HEIGHT];

static inline void
setPixel(const int x, const int y, const uint32_t color)
{
  if (x < 0 || y < 0 || x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT)
    return;
  display[y * DISPLAY_WIDTH + x] = color;
}
