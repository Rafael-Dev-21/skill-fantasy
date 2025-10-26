#include <math.h>

#include "noise.h"
#include "math.h"

#ifndef M_PI
#define M_PI 3.1415926535897
#endif

FBMParams default_fbm = {
	1.0,
	1.0,
	2.0,
	0.5,
	3,
	perlin2d
};

static Vec2 grad(int ix, int iy)
{
	float angle = hash_posf(ix, iy) * (M_PI * 2.0);

	Vec2 ret;

	ret.x = cos(angle);
	ret.y = sin(angle);

	return ret;
}

float value2d(float x, float y)
{
	int ix = (int)floor(x);
	int iy = (int)floor(y);
	float fx = x - ix;
	float fy = y - iy;
	float u = smoother(fx);
	float v = smoother(fy);

	float h1 = hash_posf(ix, iy);
	float h2 = hash_posf(ix + 1, iy);
	float h3 = hash_posf(ix, iy + 1);
	float h4 = hash_posf(ix + 1, iy + 1);

	return lerp(lerp(h1, h2, u), lerp(h3, h4, u), v) * 2.0 - 1.0;
}

float perlin2d(float x, float y)
{
	int ix = (int)floor(x);
	int iy = (int)floor(y);
	float fx = x - ix;
	float fy = y - iy;
	float u = smoother(fx);
	float v = smoother(fy);

	Vec2 g1 = grad(ix, iy);
	Vec2 g2 = grad(ix + 1, iy);
	Vec2 g3 = grad(ix, iy + 1);
	Vec2 g4 = grad(ix + 1, iy + 1);

	Vec2 d1 = {fx, fy};
	Vec2 d2 = {fx - 1, fy};
	Vec2 d3 = {fx, fy - 1};
	Vec2 d4 = {fx - 1, fy - 1};

	float n0, n1, x0, x1, value;
	n0 = dot(g1, d1);
	n1 = dot(g2, d2);
	x0 = lerp(n0, n1, u);
	n0 = dot(g3, d3);
	n1 = dot(g4, d4);
	x1 = lerp(n0, n1, u);
	value = lerp(x0, x1, v);
	return value;
}

float simplex2d(float x, float y)
{
	float n0, n1, n2;

	const float F2 = 0.5 * (float)(sqrt(3.0) - 1.0);
	float s = (x+y)*F2;
	int i = (int)floor(x+s);
	int j = (int)floor(y+s);
	const float G2 = (float)(3.0 - sqrt(3.0)) / 6.0;
	float t = (i+j)*G2;
	float X0 = i-t;
	float Y0 = j-t;
	float x0 = x-X0;
	float y0 = y-Y0;

	int i1, j1;
	if (x0>y0) {
		i1 = 1;
		j1 = 0;
	} else {
		i1 = 0;
		j1 = 1;
	}

	float x1 = x0 - i1 + G2;
	float y1 = y0 - j1 + G2;
	float x2 = x0 - 1.0 + 2.0 * G2;
	float y2 = y0 - 1.0 + 2.0 * G2;

	Vec2 gi0 = grad(i, j);
	Vec2 gi1 = grad(i + i1, j + j1);
	Vec2 gi2 = grad(i + 1, j + 1);

	Vec2 v0 = {x0, y0};
	Vec2 v1 = {x1, y1};
	Vec2 v2 = {x2, y2};

	float t0 = 0.5 - x0*x0-y0*y0;
	if (t0<0) {
		n0 = 0.0;
	} else {
		t0 *= t0;
		n0 = t0 * t0 * dot(gi0, v0);
	}

	float t1 = 0.5 - x1*x1-y1*y1;
	if (t1<0) {
		n1 = 0.0;
	} else {
		t1 *= t1;
		n1 = t1 * t1 * dot(gi1, v1);
	}

	float t2 = 0.5 - x2*x2-y2*y2;
	if (t2<0) {
		n2 = 0.0;
	} else {
		t2 *= t2;
		n2 = t2 * t2 * dot(gi2, v2);
	}

	return 70.0 * (n0 + n1 + n2);
}

float fbm2d(float x, float y, FBMParams params)
{
	float result = params.amplitude;
	float amp = params.amplitude;
	float freq = params.frequency;
	for (int i = 0; i < params.octaves; i += 1) {
		result += amp * params.noisefn(x * freq, y * freq);
		freq *= params.lacunarity;
		amp *= params.persistence;
	}
	return result;
}

