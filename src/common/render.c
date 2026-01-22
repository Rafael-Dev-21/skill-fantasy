#include "render.h"


void clearDisplay(uint32_t color)
{
  int i;
  for (i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
    display[i] = color;
}

void fillCircle(int cx, int cy, int cr, uint32_t color)
{
  int i, j, x, y, crsqr;
  crsqr = cr * cr;
  for (j = -cr; j < cr; j++)  {
    for (i = -cr; i < cr; i++) {
      if (i * i + j * j >= crsqr) {
        continue;
      }
      x = cx + i;
      y = cy + j;
      setPixel(x, y, color);
    }
  }
}

void strokeCircle(int cx, int cy, int cr, uint32_t color)
{
  int t1, t2, x, y, i, px, py;
  t1 = cr / 16;
  x = cr;
  y = 0;
  while (x >= y) {
    {
      px = cx + x;
      py = cy + y;
      setPixel(px, py, color);
    }
    {
      px = cx + y;
      py = cy + x;
      setPixel(px, py, color);
    }
    {
      px = cx - x;
      py = cy + y;
      setPixel(px, py, color);
    }
    {
      px = cx - y;
      py = cy + x;
      setPixel(px, py, color);
    }
    {
      px = cx + x;
      py = cy - y;
      setPixel(px, py, color);
    }
    {
      px = cx + y;
      py = cy - x;
      setPixel(px, py, color);
    }
    {
      px = cx - x;
      py = cy - y;
      setPixel(px, py, color);
    }
    {
      px = cx - y;
      py = cy - x;
      setPixel(px, py, color);
    }
    y = y + 1;
    t1 = t1 + y;
    t2 = t1 - x;
    if (t2 >= 0) {
      t1 = t2;
      x = x - 1;
    }
  }
}


void strokeLine(int x1, int y1, int x2, int y2, uint32_t color)
{
  int steep = absi(x1-x2) < absi(y1-y2);
  if (steep) {
    swapi(&x1, &y1);
    swapi(&x2, &y2);
  }
  if (x1>x2) {
    swapi(&x1, &x2);
    swapi(&y1, &y2);
  }
  int y = y1;
  int ierror = 0;
  for (int x=x1; x<=x2; x++) {
    if (steep)
      setPixel(y, x, color);
    else
      setPixel(x, y, color);
    ierror += 2 * absi(y2-y1);
    y += (y2 > y1 ? 1 : -1) * (ierror > x2 - x1);
    ierror -= 2 * (x2-x1)   * (ierror > x2 - x1);
  }
}

void fillTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint32_t color)
{
  if (ay>by) { swapi(&ax, &bx); swapi(&ay, &by); }
  if (ay>cy) { swapi(&ax, &cx); swapi(&ay, &cy); }
  if (by>cy) { swapi(&bx, &cx); swapi(&by, &cy); }
  int total_height = cy-ay;
  if (ay!=by) {
    int segment_height = by-ay;
    for (int y=ay; y<=by; y++) {
      int x0 = ax + ((cx-ax)*(y-ay)) / total_height;
      int x1 = ax + ((bx-ax)*(y-ay)) / segment_height;
      for (int x=imin(x0,x1); x<=imax(x0,x1); x++)
        setPixel(x, y, color);
    }
  }
  if (by!=cy) {
    int segment_height = cy-by;
    for (int y=by; y<=cy; y++) {
      int x0 = ax + ((cx-ax)*(y-ay)) / total_height;
      int x1 = bx + ((cx-bx)*(y-by)) / segment_height;
      for (int x=imin(x0,x1); x<=imax(x0,x1); x++)
        setPixel(x, y, color);
    }
  }
}
void strokeTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint32_t color)
{
  strokeLine(ax, ay, bx, by, color);
  strokeLine(bx, by, cx, cy, color);
  strokeLine(cx, cy, ax, ay, color);
}
static inline float signed_triangle_area(int ax, int ay, int bx, int by, int cx, int cy)
{
  return .5f*((by-ay)*(bx+ax) + (cy-by)*(cx+bx) + (ay-cy)*(ax+cx));
}
void blitTriangle(int ax, int ay, int bx, int by, int cx, int cy, int tax, int tay, int tbx, int tby, int tcx, int tcy, const Surface * restrict s)
{
  if (ay>by) { swapi(&ax, &bx); swapi(&ay, &by); }
  if (ay>cy) { swapi(&ax, &cx); swapi(&ay, &cy); }
  if (by>cy) { swapi(&bx, &cx); swapi(&by, &cy); }
  float total_area = signed_triangle_area(ax,ay,bx,by,cx,cy);
  int total_height = cy-ay;
  if (ay!=by) {
    int segment_height = by-ay;
    for (int y=ay; y<=by; y++) {
      int x0 = ax + ((cx-ax)*(y-ay)) / total_height;
      int x1 = ax + ((bx-ax)*(y-ay)) / segment_height;
      for (int x=imin(x0,x1); x<=imax(x0,x1); x++) {
        float alpha = signed_triangle_area(x, y, bx, by, cx, cy) / total_area;
        float beta = signed_triangle_area(x, y, cx, cy, ax, ay) / total_area;
        float gamma = signed_triangle_area(x, y, ax, ay, bx, by) / total_area;
        int tx = (int)(tax * alpha + tbx * beta + tcx * gamma);
        int ty = (int)(tay * alpha + tby * beta + tcy * gamma);
        uint32_t color = Surface_get_pixel(s, tx, ty);
        setPixel(x, y, color);
      }
    }
  }
  if (by!=cy) {
    int segment_height = cy-by;
    for (int y=by; y<=cy; y++) {
      int x0 = ax + ((cx-ax)*(y-ay)) / total_height;
      int x1 = bx + ((cx-bx)*(y-by)) / segment_height;
      for (int x=imin(x0,x1); x<=imax(x0,x1); x++) {
        float alpha = signed_triangle_area(x, y, bx, by, cx, cy) / total_area;
        float beta = signed_triangle_area(x, y, cx, cy, ax, ay) / total_area;
        float gamma = signed_triangle_area(x, y, ax, ay, bx, by) / total_area;
        int tx = (int)(tax * alpha + tbx * beta + tcx * gamma);
        int ty = (int)(tay * alpha + tby * beta + tcy * gamma);
        uint32_t color = Surface_get_pixel(s, tx, ty);
        setPixel(x, y, color);
      }
    }
  }
}
