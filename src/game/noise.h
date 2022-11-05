#ifndef NOISE_H
#define NOISE_H

#include <functional>

// math
namespace noise {
float lerp(float x, float y, float s);
float noise2d(float x, float y);
float fbm(float x, float y, float freq, int depth, std::function<float(float, float)> noise_fn);
};  // namespace noise

#endif
