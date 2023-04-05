#include "math.hpp"

float lerp(float a, float b, float t) {
  return (1 - t) * a + t * b;
}

float smoothstep(float a, float b, float t) {
  return lerp(a, b, t * t * (3 - 2 * t));
}

float easeIn(float value) {
  return value * value;
}

float easeOut(float value) {
  return 1 - easeIn(1 - value);
}

float easeInOut(float value) {
  float in = easeIn(value);
  float out = easeOut(value);
  return lerp(in, out, value);
}

