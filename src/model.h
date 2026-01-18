#pragma once

#include "vec.h"

typedef struct {
  v3     *vert;
  size_t *face;
  size_t vcount;
  size_t vcap;
  size_t fcount;
  size_t fcap;
} Model;

void Model_init(Model * restrict m);
void Model_load(Model * restrict m, const char * restrict filename);
void Model_renderWireFrame(const Model * restrict m,
    v2 (*projFn)(const v3),
    uint32_t color);
void Model_renderFlatRC(const Model * restrict m,
    v2 (*projFn)(const v3));
