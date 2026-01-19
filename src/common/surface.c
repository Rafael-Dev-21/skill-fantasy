#include "surface.h"
#include "util.h"

void Surface_init(
    Surface *s,
    size_t width,
    size_t height,
    uint32_t *buf,
    size_t pitch)
{
  s->pixels = buf;
  s->width = width;
  s->height = height;
  s->pitch = pitch;
}

void Surface_set_pixel(Surface *s, int x, int y, uint32_t val)
{
  if (x < 0 || y < 0 || x >= s->width || y >= s->height) return;
  s->pixels[x + y * s->pitch] = val;
}

uint32_t Surface_get_pixel(const Surface *s, int x, int y)
{
  if (x < 0 || y < 0 || x >= s->width || y >= s->height) return 0;
  return s->pixels[x + y * s->pitch];
}

void Surface_blit(Surface *dst, int dx, int dy,
    const Surface *src, int sx, int sy, int sw, int sh)
{
  dx = iclamp(dx, 0, dst->width-sw);
  dy = iclamp(dy, 0, dst->height-sh);
  sx = iclamp(sx, 0, src->width-sw);
  sy = iclamp(sy, 0, src->height-sh);
  uint32_t *dstline = dst->pixels + dx + dy * dst->pitch;
  uint32_t *srcline = src->pixels + sx + sy * src->pitch;
  for (int y=0; y<sh; y++) {
    for (int x=0; x<sw; x++) {
      uint32_t v = srcline[x];
      uint32_t o = dstline[x];
      uint32_t a = (v>>24)+1;
      uint32_t inv_a = 256 - a;
      uint32_t rb = ((v & 0xFF00FF) * a + (o & 0xFF00FF) * inv_a) >> 8;
      uint32_t g = ((v & 0x00FF00) * a + (o & 0x00FF00) * inv_a) >> 8;
      dstline[x] = (rb & 0xFF00FF) | (g & 0x00FF00) | 0xFF000000;
    }
    srcline += src->pitch;
    dstline += dst->pitch;
  }
}
