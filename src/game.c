#include "game.h"
#include "memory.h"
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define FPS 30

#define DISPLAY_WIDTH  640
#define DISPLAY_HEIGHT 480

#define BLACK   0xFF000000
#define CYAN    0xFF00FFFF
#define MAGENTA 0xFFFF00FF
#define YELLOW  0xFFFFFF00
#define WHITE   0xFFFFFFFF
#define BLUE    0xFF0000FF
#define RED     0xFFFF0000
#define GREEN   0xFF00FF00

#define max(a, b) (((a)>(b))?(a):(b))
#define min(a, b) (((a)<(b))?(a):(b))
#define clamp(x, mn, mx) (max((mn), (min((mx), (x)))))

typedef float float2[2];
typedef float float3[3];
typedef float float4[4];

typedef struct {
  float2 joints[256];
  float  angles[256];
  float  angleConstraint;
  int    linkSize;
  size_t count;
} Chain;

typedef struct {
  float3 *vert;
  size_t *face;
  size_t vcount;
  size_t vcap;
  size_t fcount;
  size_t fcap;
} Model;

static void
Model_init(Model *m);
static void
Model_load(Model *m, const char *filename);
static void
Model_renderWireFrame(const Model *m,
    void (*projFn)(float2, const float3),
    uint32_t color);

static void
Model_renderFlatRC(const Model *m,
    void (*projFn)(float2, const float3));

static inline void
fn_set(const size_t n, float * restrict dst, const float val)
{
  for (size_t i=0; i<n; i++)
    dst[i] = val;
}
static inline void
fn_setAll(float * restrict dst, const size_t n, ...)
{
  va_list va;
  va_start(va, n);
  for (size_t i=0; i<n; i++)
    dst[i] = va_arg(va, double);
  va_end(va);
}
static inline void
fn_cpy(const size_t n, float * restrict dst, const float * restrict src)
{
  for (size_t i=0; i<n; i++)
    dst[i] = src[i];
}
static inline void
fn_add(const size_t n, float * restrict dst, const float * restrict a, const float * restrict b)
{
  size_t i;
  for (i = 0; i < n; i++)
    dst[i] = a[i] + b[i];
}
static inline void
fn_sub(const size_t n, float * restrict dst, const float * restrict a, const float * restrict b)
{
  size_t i;
  for (i = 0; i < n; i++)
    dst[i] = a[i] - b[i];
}
static inline void
fn_mul(const size_t n, float * restrict dst, const float * restrict a, const float b)
{
  size_t i;
  for (i = 0; i < n; i++)
    dst[i] = a[i] * b;
}
static inline void
fn_div(const size_t n, float * restrict dst, const float * restrict a, const float b)
{
  if (b == 0) {
    memset(dst, 0, sizeof(float)*n);
    return;
  }
  size_t i;
  for (i = 0; i < n; i++)
    dst[i] = a[i] / b;
}
static inline float
fn_lenSqr(const size_t n, const float * restrict fv)
{
  int i;
  float r;
  r = 0;
  for (i = 0; i < n; i++)
    r += fv[i] * fv[i];
  return r;
}
static inline float
fn_len(const size_t n, const float * restrict fv)
{
  const float lsqr = fn_lenSqr(n, fv);
  if (lsqr == 0) {
    return 0;
  }
  return sqrtf(lsqr);
}
static inline void
fn_setMag(const size_t n, float * restrict dst, const float * restrict a, float mag)
{
  size_t i;
  const float len = fn_len(n, a);
  if (len == 0) {
    memset(dst, 0, sizeof(float)*n);
    return;
  }
  for (i=0; i<n; i++)
    dst[i] = a[i] / len * mag;
}


static uint32_t display[DISPLAY_WIDTH * DISPLAY_HEIGHT];
static int display_dirty = 0, mouseX = 0, mouseY = 0;
static Chain worm;

static inline void setPixel(const int x, const int y, const uint32_t color)
{
  if (x < 0 || y < 0 || x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT)
    return;
  display[y * DISPLAY_WIDTH + x] = color;
}
static void clearDisplay(uint32_t color);
static void fillCircle(int cx, int cy, int cr, uint32_t color);
static void strokeCircle(int cx, int cy, int cr, uint32_t color);
static void strokeLine(int x1, int y1, int x2, int y2, uint32_t color);
static void fillTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint32_t color);
static void strokeTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint32_t color);
static int absi(int i);
static void swapi(int *a, int *b);

void constrainDistance(int n, float *dst, const float *pos, const float *anchor, const float constraint) {
  fn_sub(n, dst, pos, anchor);
  fn_setMag(n, dst, dst, constraint);
  fn_add(n, dst, pos, dst);
}

float simplifyAngle(float angle)
{
  while (angle >= 2*M_PI) {
    angle -= 2*M_PI;
  }
  while (angle < 0) {
    angle += 2*M_PI;
  }
  return angle;
}

float relativeAngleDiff(float angle, float anchor)
{
  angle = simplifyAngle(angle + M_PI - anchor);
  anchor = M_PI;

  return anchor - angle;
}

float constrainAngle(float angle, float anchor, float constraint)
{
  if (fabs(relativeAngleDiff(angle, anchor)) <= constraint)
    return simplifyAngle(angle);
  if (relativeAngleDiff(angle, anchor) > constraint)
    return simplifyAngle(anchor - constraint);
  return simplifyAngle(anchor + constraint);
}

static void
Chain_init(Chain *self, const float2 origin, const size_t jointCount,
    const int linkSize, const float angleConstraint)
{
  size_t i;
  float2 dist = { 0.0f, linkSize };
  self->linkSize = linkSize;
  self->count = jointCount;
  self->angleConstraint = angleConstraint;
  self->angles[0] = 0.0f;
  fn_cpy(2, self->joints[0], origin);
  for (i = 1; i < jointCount; i++) {
    fn_add(2, self->joints[i], self->joints[i-1], dist);
    self->angles[i] = 0.0f;
  }
}
static void
Chain_resolve(Chain *self, const float2 pos)
{
  int i;
  float2 heading;
  float curAngle;
  fn_sub(2, heading, pos, self->joints[0]);
  self->angles[0] = atan2f(heading[1], heading[0]);
  fn_cpy(2, self->joints[0], pos);
  for (i = 1; i < self->count; i++) {
    fn_sub(2, heading, self->joints[i-1], self->joints[i]);
    curAngle = atan2f(heading[1], heading[0]);
    self->angles[i] = constrainAngle(curAngle, self->angles[i-1], self->angleConstraint);
    fn_setAll(heading, 2,
        cosf(self->angles[i]),
        sinf(self->angles[i]));
    fn_setMag(2, heading, heading, self->linkSize);
    fn_sub(2, self->joints[i], self->joints[i-1], heading);
  }
}
static void
Chain_fabrikResolve(Chain *self,
    const float2 pos, const float2 anchor)
{
  fn_cpy(2, self->joints[0], pos);
  for (size_t i=1; i<self->count; i++)
    constrainDistance(2, self->joints[i], self->joints[i], self->joints[i-1], self->linkSize);

  fn_cpy(2, self->joints[self->count-1], anchor);
  for (int i=(int)self->count-2; i>=0; i--)
    constrainDistance(2, self->joints[i], self->joints[i], self->joints[i+1], self->linkSize);
}

void
Chain_display(const Chain * restrict self)
{
  size_t i;
  float2 start, end, joint;
  for (i = 0; i < self->count-1; i++) {
    fn_cpy(2, start, self->joints[i]);
    fn_cpy(2, end, self->joints[i+1]);
    strokeLine((int)start[0], (int)start[1],
        (int)end[0], (int)end[1], WHITE);
  }

  for (i = 0; i < self->count; i++) {
    fn_cpy(2, joint, self->joints[i]);
    strokeCircle((int)joint[0], (int)joint[1], 10, WHITE);
  }
}

static uint32_t getGroundColor(int x, int y)
{
  unsigned int h = (unsigned int)(x * 374761393 + y * 668265263);
  h = (h ^ (h >> 13)) * 1274126177;
  int brightness = (h % 30);
  return 0xFF004400 | (brightness << 8);
}

Model pose;

Game Game_init(void)
{
  float2 origin = { DISPLAY_WIDTH /2.0, DISPLAY_HEIGHT /2.0 };
  display_dirty = 1;
  Chain_init(&worm, origin, 48, 21, M_PI/8);
  Model_init(&pose);
  Model_load(&pose, "data/diablo3_pose.obj");
  Game g = {
    FPS,
    display,
    DISPLAY_WIDTH,
    DISPLAY_HEIGHT
  };
  return g;
}

static void ortho(float2 v2, const float3 v3)
{
  v2[0] = (v3[0]+1.f) * DISPLAY_WIDTH/2;
  v2[1] = (1.f-v3[1]) * DISPLAY_HEIGHT/2;
}

static void cabinet(float2 v2, const float3 v3)
{
  float cos45 = 0.7071f;
  float sin45 = 0.7071f;
  float depthScale = 0.5f;
  v2[0] = v3[0] + (v3[1] * cos45 * depthScale);
  v2[1] = v3[2] - (v3[1] * sin45 * depthScale);

  v2[0] *= 64.0f;
  v2[1] *= 64.0f;
  v2[0] += DISPLAY_WIDTH/2;
  v2[1] += DISPLAY_HEIGHT/2;
}

void Game_update(void)
{
  float2 target, diff, next;
  clearDisplay(BLACK);

//  for (int i = 0; i < DISPLAY_HEIGHT; i++)
//    for (int j = 0; j < DISPLAY_WIDTH; j++)
//      setPixel(j, i, getGroundColor(j, i));

  fn_setAll(target, 2, (float)mouseX, (float)mouseY);
  fn_sub(2, diff, target, worm.joints[0]);

  float dist = fn_len(2, diff);
  if (dist > 1.0f) {
    float moveDist = min(dist, 12.0f);
    fn_setMag(2, diff, diff, moveDist);
    fn_add(2, next, worm.joints[0], diff);
    Chain_resolve(&worm, next);
  }

  Model_renderFlatRC(&pose, ortho);
  Chain_display(&worm);
}

void Game_mouseMove(int x, int y)
{
  mouseX = clamp(x, 0, DISPLAY_WIDTH-1);
  mouseY = clamp(y, 0, DISPLAY_HEIGHT-1);
}

static void clearDisplay(uint32_t color)
{
  int i;
  for (i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
    display[i] = color;
}

static void fillCircle(int cx, int cy, int cr, uint32_t color)
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

static void strokeCircle(int cx, int cy, int cr, uint32_t color)
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

static void swapi(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

static int absi(int i)
{
  if (i < 0) return -i;
  else return i;
}

static void strokeLine(int x1, int y1, int x2, int y2, uint32_t color)
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

static inline double
signedTriangleArea(int ax, int ay, int bx, int by, int cx, int cy)
{
  return .5*((by-ay)*(bx+ax) + (cy-by)*(cx+bx) + (ay-cy)*(ax+cx));
}

static void fillTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint32_t color)
{
  int bbminx = min(min(ax, bx), cx);
  int bbminy = min(min(ay, by), cy);
  int bbmaxx = max(max(ax, bx), cx);
  int bbmaxy = max(max(ay, by), cy);
  double totalArea = signedTriangleArea(ax, ay, bx, by, cx, cy);
  if (totalArea<1) return;

#pragma omp parallel for
  for (int x=bbminx; x<=bbmaxx; x++) {
    for (int y=bbminy; y<=bbmaxy; y++) {
      double alpha = signedTriangleArea(x, y, bx, by, cx, cy) / totalArea;
      double beta  = signedTriangleArea(x, y, cx, cy, ax, ay) / totalArea;
      double gamma = signedTriangleArea(x, y, ax, ay, bx, by) / totalArea;
      if (alpha<0 || beta<0 || gamma<0) continue;
      setPixel(x, y, color);
    }
  }
}
static void strokeTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint32_t color)
{
  strokeLine(ax, ay, bx, by, color);
  strokeLine(bx, by, cx, cy, color);
  strokeLine(cx, cy, ax, ay, color);
}

static void
Model_init(Model *m)
{
  m->vert = NULL;
  m->face = NULL;
  m->vcount = 0;
  m->fcount = 0;
  m->vcap = 0;
  m->fcap = 0;
}

static void
Model_addVert(Model *m, const float3 v)
{
  if (m->vcount + 1 > m->vcap) {
    int oldCap = m->vcap;
    m->vcap = GROW_CAPACITY(oldCap);
    m->vert = GROW_ARRAY(float3, m->vert, oldCap, m->vcap);
  }
  fn_cpy(3, m->vert[m->vcount++], v);
}

static void
Model_addFace(Model *m, const size_t f)
{
  if (m->fcount + 1 > m->fcap) {
    int oldCap = m->fcap;
    m->fcap = GROW_CAPACITY(oldCap);
    m->face = GROW_ARRAY(size_t, m->face, oldCap, m->fcap);
  }
  m->face[m->fcount++] = f;
}

static void
Model_load(Model *m, const char *filename)
{
  char buffer[1024] = {0};
  float3 v;
  size_t f;
  FILE *fp;
  char *tok;

  fp = fopen(filename, "r");

  while (fgets(buffer, 1023, fp)) {
    if (buffer[0]=='v' && buffer[1]==' ') {
      tok = strtok(buffer, " ");
      for (int i = 0; i < 3; i++) {
        tok = strtok(NULL, " \n");
        v[i] = atof(tok);
      }
      Model_addVert(m, v);
    }
    else if (buffer[0]=='f' && buffer[1]==' ') {
      tok = strtok(buffer, " ");
      for (int i = 0; i < 3; i++) {
        tok = strtok(NULL, "/");
        f = atoi(tok);
        strtok(NULL, " \n");
        Model_addFace(m, f-1);
      }
    }
  }

  fclose(fp);
}

static void
Model_renderWireFrame(const Model *m,
    void (*projFn)(float2, const float3),
    uint32_t color)
{
  float3 v1, v2, v3;
  float2 s1, s2, s3;
  size_t *f;

  for (int i = 0; i < m->fcount/3; i++) {
    f = &m->face[i*3];
    fn_cpy(3, v1, m->vert[f[0]]);
    projFn(s1, v1);
    fn_cpy(3, v2, m->vert[f[1]]);
    projFn(s2, v2);
    fn_cpy(3, v3, m->vert[f[2]]);
    projFn(s3, v3);

    strokeTriangle(
        (int)s1[0], (int)s1[1],
        (int)s2[0], (int)s2[1],
        (int)s3[0], (int)s3[1],
        color);
  }
}

static void
Model_renderFlatRC(const Model *m,
    void (*projFn)(float2, const float3))
{
  float3 v1, v2, v3;
  float2 s1, s2, s3;
  size_t *f;
  uint32_t rnd;

  for (int i = 0; i < m->fcount/3; i++) {
    f = &m->face[i*3];
    fn_cpy(3, v1, m->vert[f[0]]);
    projFn(s1, v1);
    fn_cpy(3, v2, m->vert[f[1]]);
    projFn(s2, v2);
    fn_cpy(3, v3, m->vert[f[2]]);
    projFn(s3, v3);

    rnd = 0xFF;
    for (int c=0; c<3; c++) rnd = (rnd<<8) | ((((int)s1[0]*(int)s1[1])^((int)s2[0]*(int)s2[1])^((int)s3[0]*(int)s3[1]))%256);

    fillTriangle(
        (int)s1[0], (int)s1[1],
        (int)s2[0], (int)s2[1],
        (int)s3[0], (int)s3[1],
        rnd);
  }
}
