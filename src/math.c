#include "mymath.h"

float lerp(float a, float b, float t)
{
	if (t < 0) return a;
	if (t > 1) return b;
	return a + (b - a) * t;
}

float smooth(float t)
{
	return (3.0 - t * 2.0) * t * t;
}

float smoother(float t)
{
	return (t * (t * 6.0 - 15.0) + 10.0) * t * t * t;
}

float normalize(float value, float min, float max)
{
	return (value - min) / (max - min);
}

float hash_posf(int x, int y)
{
	return hash_pos(x, y) * (1.0 / ~0u);
}

size_t hash_pos(int x, int y)
{
	const size_t w = 8 * sizeof(size_t);
	const size_t s = w / 2;

	size_t a = x, b = y;

	a *= 3284157443; b ^= a << s | a >> w-s;
	b *= 1911520717; a ^= b << s | b >> w-s;
	a *= 2048419325;

	return a;
}

float dot(Vec2 a, Vec2 b)
{
	return a.x * b.x + a.y * b.y;
}
