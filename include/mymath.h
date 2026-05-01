#ifndef MYMATH_H
#define MYMATH_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
	float x;
	float y;
} Vec2;

// math
float lerp(float a, float b, float t);
float smooth(float t);
float smoother(float t);
float normalize(float value, float min, float max);
float hash_posf(int x, int y);
size_t hash_pos(int x, int y);
float dot(Vec2 a, Vec2 b);

#endif
