#pragma once

#include "vec.h"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

static inline int imax(int a, int b)
{ return (a>b)?a:b; }
static inline int imin(int a, int b)
{ return (a<b)?a:b; }
static inline int iclamp(int x, int mn, int mx)
{ return imax(mn, imin(mx, x)); }

static inline void
swapi(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

static inline int
absi(int i)
{
  if (i < 0) return -i;
  else return i;
}


static inline v2
constrainDistance(const v2 pos, const v2 anchor, const float constraint)
{
  return v2_add(pos, v2_with_len(v2_sub(pos, anchor), constraint));
}

static inline float
simplifyAngle(float angle)
{
  angle = fmodf(angle, 2*M_PI);
  if (angle < 0) angle += 2*M_PI;
  return angle;
}

static inline float
relativeAngleDiff(float angle, float anchor)
{
  return M_PI - simplifyAngle(angle + M_PI - anchor);
}

static inline float
constrainAngle(float angle, float anchor, float constraint)
{
  if (fabs(relativeAngleDiff(angle, anchor)) <= constraint)
    return simplifyAngle(angle);
  if (relativeAngleDiff(angle, anchor) > constraint)
    return simplifyAngle(anchor - constraint);
  return simplifyAngle(anchor + constraint);
}
