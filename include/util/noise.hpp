#pragma once

#include <vector>

#include "geom.hpp"

struct FBMParams {
  float frequency = 1.0;
  float amplitude = 1.0;
  float lacunarity = 2.0;
  float persistence = 0.5;
  int octaves = 3;
};

class Noise {
 public:
  virtual float value(float x, float y) = 0;
  float fbm(float x, float y, FBMParams params = {});
};

class Perlin : public Noise {
 public:
  Perlin();

  float value(float x, float y) override;
  void calcPermutations();

 private:
  float dotGradient(int hash, float x, float y);

  int perms[512];

  static FVector grads[8];
};

class Simplex : public Noise {
 public:
  Simplex();

  float value(float x, float y) override;
  void calcPermutations();

 private:
  float dotGradient(int g[3], float x, float y);

  int perms[512];
  static int grads[12][3];
};