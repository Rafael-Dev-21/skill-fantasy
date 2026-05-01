#ifndef MYUTIL_H
#define MYUTIL_H

#include <stdint.h>
#include <stddef.h>
#include "vec.h"

// util
float lerp(float a, float b, float t);
float smooth(float t);
float smoother(float t);
float normalize(float value, float min, float max);
float hash_posf(int x, int y);
size_t hash_pos(int x, int y);

#endif
