#pragma once

#include <stdint.h>
#include <stddef.h>
#include "util.h"

typedef struct {
  uint32_t      *pixels;
  size_t         width;
  size_t         height;
  size_t         pitch;
} Surface;

void Surface_init(
    Surface *s,
    size_t width,
    size_t height,
    uint32_t *buf,
    size_t pitch);

void Surface_set_pixel(Surface *s, int x, int y, uint32_t val);
uint32_t Surface_get_pixel(const Surface *s, int x, int y);
void Surface_blit(Surface *dst, int dx, int dy,
    const Surface *src, int sx, int sy, int sw, int sh);
