#include "math.hpp"
#include <cmath>

float Math::lerp(float a, float b, float t)
{
	if (0.0 > t) return a;
	if (1.0 < t) return b;
	return (b - a) * t + a;
}

float Math::smooth(float t)
{
	return (3.0 - t * 2.0) * t * t;
}

float Math::smoother(float t)
{
	return (t * (t * 6.0 - 15.0) + 10.0) * t * t * t;
}

float Math::normalize(float value, float min, float max)
{
	return (value - min) / (max - min);
}
