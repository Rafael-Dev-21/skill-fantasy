#pragma once

#include <stdint.h>
#include <stddef.h>
#include "vec.h"

typedef struct {
  v2     joints[256];
  float  angles[256];
  float  angleConstraint;
  int    linkSize;
  size_t count;
} Chain;

void Chain_init(Chain * restrict self, const v2 origin,
    const size_t jointCount, const int linkSize, const float angleConstraint);
void Chain_resolve(Chain * restrict self, const v2 pos);
void Chain_fabrikResolve(Chain * restrict self, const v2 pos,
    const v2 anchor);
void Chain_display(const Chain * restrict self);
