#pragma once

#include "vec.h"
#include "surface.h"

typedef struct {
  v3     *vert;
  v2     *texc;
  size_t *face;
  size_t vcount;
  size_t fcount;
} Model;

void Model_init(Model * restrict m);
void Model_renderWireFrame(const Model * restrict m,
    v2 (*projFn)(const v3),
    uint32_t color);
void Model_renderFlatRC(const Model * restrict m,
    v2 (*projFn)(const v3));
void Model_renderFlatTex(const Model * restrict m,
    v2 (*projFn)(const v3),
    const Surface * restrict s);
