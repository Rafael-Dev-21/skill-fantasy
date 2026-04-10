#ifndef NOISE_H
#define NOISE_H

// math
float lerp(float x, float y, float s);
float noise2d(float x, float y);
float fbm(float x, float y, float freq, int depth);

#endif
