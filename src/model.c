#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "model.h"
#include "render.h"

static void
Model_addVert(Model * restrict m, const v3 v);
static void
Model_addFace(Model * restrict m, const size_t f);

void
Model_init(Model * restrict m)
{
  m->vert = NULL;
  m->face = NULL;
  m->vcount = 0;
  m->fcount = 0;
  m->vcap = 0;
  m->fcap = 0;
}

void
Model_load(Model * restrict m, const char * restrict filename)
{
  static char buffer[1024] = {0};
  v3 v;
  size_t f;
  FILE *fp;
  char *tok;

  fp = fopen(filename, "r");
  if (!fp) return;

  while (fgets(buffer, 1023, fp)) {
    if (buffer[0]=='v' && buffer[1]==' ') {
      tok = strtok(buffer, " ");
      tok = strtok(NULL, " \n");
      v.x = atof(tok);
      tok = strtok(NULL, " \n");
      v.y = atof(tok);
      tok = strtok(NULL, " \n");
      v.z = atof(tok);
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

void
Model_renderWireFrame(const Model * restrict m,
    v2 (*projFn)(const v3),
    uint32_t color)
{
  for (int i = 0; i < m->fcount/3; i++) {
    size_t *f = &m->face[i*3];
    v3 A = m->vert[f[0]];
    v2 a = projFn(A);
    v3 B = m->vert[f[1]];
    v2 b = projFn(B);
    v3 C = m->vert[f[2]];
    v2 c = projFn(C);

    strokeTriangle(
        (int)a.x, (int)a.y,
        (int)b.x, (int)b.y,
        (int)c.x, (int)c.y,
        color);
  }
}

static inline float signed_triangle_area(v2 a, v2 b, v2 c)
{
  return .5f*((b.y-a.y)*(b.x+a.x) + (c.y-b.y)*(c.x+b.x) + (a.y-c.y)*(a.x+c.x));
}

void
Model_renderFlatRC(const Model * restrict m,
    v2 (*projFn)(const v3))
{
  for (int i = 0; i < m->fcount/3; i++) {
    size_t *f = &m->face[i*3];
    v3 A = m->vert[f[0]];
    v2 a = projFn(A);
    v3 B = m->vert[f[1]];
    v2 b = projFn(B);
    v3 C = m->vert[f[2]];
    v2 c = projFn(C);

    if (signed_triangle_area(a, b, c)<1) continue;

    /*
    uint32_t rnd = 0xFF;
    for (int j=1; j<=3; j++) rnd = (rnd<<8) | (((i * 4294967279u) ^ (j * 4294967291u)) & 255u);
    */
    uint32_t rnd = 0xFF000000 | (i * 2654435761u);

    fillTriangle(
        (int)a.x, (int)a.y,
        (int)b.x, (int)b.y,
        (int)c.x, (int)c.y,
        rnd);
  }
}

static void
Model_addVert(Model * restrict m, const v3 v)
{
  if (m->vcount + 1 > m->vcap) {
    int oldCap = m->vcap;
    m->vcap = GROW_CAPACITY(oldCap);
    m->vert = GROW_ARRAY(v3, m->vert, oldCap, m->vcap);
  }
  m->vert[m->vcount++] = v;
}

static void
Model_addFace(Model * restrict m, const size_t f)
{
  if (m->fcount + 1 > m->fcap) {
    int oldCap = m->fcap;
    m->fcap = GROW_CAPACITY(oldCap);
    m->face = GROW_ARRAY(size_t, m->face, oldCap, m->fcap);
  }
  m->face[m->fcount++] = f;
}
