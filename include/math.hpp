#pragma once

#include <cmath>

namespace Math {
float lerp(float a, float b, float t);
float smooth(float t);
float smoother(float t);
float normalize(float value, float min, float max);
float hash(int x, int y);
};  // namespace Math
