#pragma once

#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>

typedef struct { float x, y; } v2;
typedef struct { float x, y, z; } v3;

static inline v2 v2_add(v2 a, v2 b) { return (v2){a.x + b.x, a.y + b.y}; }
static inline v2 v2_sub(v2 a, v2 b) { return (v2){a.x - b.x, a.y - b.y}; }
static inline v2 v2_mul(v2 a, float s) { return (v2){a.x * s, a.y * s}; }
static inline float v2_dot(v2 a, v2 b) { return a.x * b.x + a.y * b.y; }
static inline float v2_len_sqr(v2 v) { return v.x * v.x + v.y * v.y; }
static inline float v2_len(v2 v) { return sqrtf(v2_len_sqr(v)); }
static inline v2 v2_norm(v2 v)
{
  float l = v2_len(v);
  return (l != 0) ? v2_mul(v, 1.0 / l) : (v2){0};
}
static inline float v2_angle(v2 v) { return atan2f(v.y, v.x); }
static inline v2 v2_polar(float angle, float len)
{ return (v2){ cosf(angle) * len, sinf(angle) * len }; }
static inline v2 v2_with_len(v2 v, float l)
{ return v2_mul(v2_norm(v), l); }

static inline v3 v3_add(v3 a, v3 b)
{ return (v3){a.x + b.x, a.y + b.y, a.z + b.z}; }
static inline v3 v3_sub(v3 a, v3 b)
{ return (v3){a.x - b.x, a.y - b.y, a.z - b.z}; }
static inline v3 v3_mul(v3 a, float s)
{ return (v3){a.x * s, a.y * s, a.z * s}; }
static inline float v3_dot(v3 a, v3 b)
{ return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline float v3_len_sqr(v3 v)
{ return v.x * v.x + v.y * v.y + v.z * v.z; }
static inline float v3_len(v3 v) { return sqrtf(v3_len_sqr(v)); }
static inline v3 v3_norm(v3 v)
{
  float l = v3_len(v);
  return (l != 0) ? v3_mul(v, 1.0 / l) : (v3){0};
}
static inline v3 v3_with_len(v3 v, float l)
{ return v3_mul(v3_norm(v), l); }
