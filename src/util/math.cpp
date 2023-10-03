#include "util/math.hpp"

float Math::lerp(float a, float b, float t) {
  if (0.0 > t) return a;
  if (1.0 < t) return b;
  return (b - a) * t + a;
}

float Math::smooth(float t) { return (3.0f - t * 2.0f) * t * t; }

float Math::smoother(float t) {
  return (t * (t * 6.0f - 15.0f) + 10.0f) * t * t * t;
}

float Math::normalize(float value, float min, float max) {
  return (value - min) / (max - min);
}

float Math::hash(int ix, int iy) {
  const unsigned w = 8 * sizeof(unsigned);
  const unsigned s = w / 2;
  
  unsigned a = ix, b = iy;
  
  a *= 3284157443; b ^= a << s | a >> (w-s);
  b *= 1911520717; a ^= b << s | b >> (w-s);
  a *= 2048419325;
  
  return a * (1.0f / ~0u);
}