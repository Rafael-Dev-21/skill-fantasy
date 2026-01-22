#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "model.h"
#include "render.h"

void
Model_init(Model * restrict m)
{
  m->vert = NULL;
  m->face = NULL;
  m->vcount = 0;
  m->fcount = 0;
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

    uint32_t rnd = 0xFF000000 | (i * 2654435761u);

    fillTriangle(
        (int)a.x, (int)a.y,
        (int)b.x, (int)b.y,
        (int)c.x, (int)c.y,
        rnd);
  }
}

void Model_renderFlatTex(const Model * restrict m,
    v2 (*projFn)(const v3),
    const Surface * restrict s)
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

    v2 TA = m->texc[f[0]];
    TA.y = 1-TA.y;
    v2 TB = m->texc[f[1]];
    TB.y = 1-TB.y;
    v2 TC = m->texc[f[2]];
    TC.y = 1-TC.y;

    v2 ta = TA;
    ta.x *= s->width;
    ta.y *= s->height;

    v2 tb = TB;
    tb.x *= s->width;
    tb.y *= s->height;

    v2 tc = TC;
    tc.x *= s->width;
    tc.y *= s->height;

    uint32_t rnd = 0xFF000000 | (i * 2654435761u);

    blitTriangle(
        (int)a.x, (int)a.y,
        (int)b.x, (int)b.y,
        (int)c.x, (int)c.y,
        (int)ta.x, (int)ta.y,
        (int)tb.x, (int)tb.y,
        (int)tc.x, (int)tc.y,
        s);
  }
}
