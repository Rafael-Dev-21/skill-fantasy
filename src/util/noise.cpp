#include "util/noise.hpp"

#include <cmath>

#include "util/math.hpp"

float Noise::fbm(float x, float y, FBMParams params) {
  float result = params.amplitude;
  float freq = params.frequency;
  float amp = params.amplitude;

  for (int i = 0; i < params.octaves; i++) {
    result += amp * value(x * freq, y * freq);
    freq *= params.lacunarity;
    amp *= params.persistence;
  }
  return result;
}

Perlin::Perlin() { calcPermutations(); }

FVector Perlin::grads[] = {FVector(1, 0),  FVector(1, -1), FVector(0, -1),
                           FVector(1, 1),  FVector(0, 1),  FVector(-1, 1),
                           FVector(-1, 0), FVector(-1, -1)};

float Perlin::value(float x, float y) {
  using namespace Math;

  int ix = (int)x & 255;
  int iy = (int)y & 255;

  float fx = x - (int)x;
  float fy = y - (int)y;

  float u = smoother(fx);
  float v = smoother(fy);

  int g1 = perms[perms[ix] + iy];
  int g2 = perms[perms[ix + 1] + iy];
  int g3 = perms[perms[ix] + iy + 1];
  int g4 = perms[perms[ix + 1] + iy + 1];

  float n1 = dotGradient(g1, fx, fy);
  float n2 = dotGradient(g2, fx - 1, fy);
  float n3 = dotGradient(g3, fx, fy - 1);
  float n4 = dotGradient(g4, fx - 1, fy - 1);

  return lerp(lerp(n1, n2, u), lerp(n3, n4, u), v);
}

void Perlin::calcPermutations() {
  using namespace Math;

  for (int i = 0; i < 256; i++) perms[i] = i;

  shuffle(perms, 256);

  for (int i = 0; i < 256; i++) perms[i + 256] = perms[i];
}

float Perlin::dotGradient(int hash, float x, float y) {
  auto gradient = grads[hash % 0x7];

  return FVector::dot(FVector(x, y), gradient);
}

Simplex::Simplex() { calcPermutations(); }

int Simplex::grads[12][3] = {{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
                             {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
                             {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}};

float Simplex::value(float x, float y) {
  float n0, n1, n2;

  const float F2 = 0.5 * (sqrt(3.0) - 1.0);
  float s = (x + y) * F2;
  int i = floor(x + s);
  int j = floor(y + s);
  const float G2 = (3.0 - sqrt(3.0)) / 6.0;
  float t = (i + j) * G2;
  float X0 = i - t;
  float Y0 = j - t;
  float x0 = x - X0;
  float y0 = y - Y0;

  int i1, j1;
  if (x0 > y0) {
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

  int ii = i & 255;
  int jj = j & 255;
  int gi0 = perms[ii + perms[jj]] % 12;
  int gi1 = perms[ii + i1 + perms[jj + j1]] % 12;
  int gi2 = perms[ii + 1 + perms[jj + 1]] % 12;

  float t0 = 0.5 - x0 * x0 - y0 * y0;
  if (t0 < 0)
    n0 = 0.0;
  else {
    t0 *= t0;
    n0 = t0 * t0 * dotGradient(grads[gi0], x0, y0);
  }

  float t1 = 0.5 - x1 * x1 - y1 * y1;
  if (t1 < 0)
    n1 = 0.0;
  else {
    t1 *= t1;
    n1 = t1 * t1 * dotGradient(grads[gi1], x1, y1);
  }

  float t2 = 0.5 - x2 * x2 - y2 * y2;
  if (t2 < 0)
    n2 = 0.0;
  else {
    t2 *= t2;
    n2 = t2 * t2 * dotGradient(grads[gi2], x2, y2);
  }

  return 70.0 * (n0 + n1 + n2);
}

void Simplex::calcPermutations() {
  using namespace Math;

  for (int i = 0; i < 256; i++) perms[i] = i;

  shuffle(perms, 256);

  for (int i = 0; i < 256; i++) perms[i + 256] = perms[i];
}

float Simplex::dotGradient(int g[3], float x, float y) {
  return g[0] * x + g[1] * y;
}