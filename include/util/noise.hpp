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
  Perlin(unsigned seed);

  float value(float x, float y) override;
  
  private:
  void calcPermutations();
  float dotGradient(int hash, float x, float y);

  std::vector<unsigned> perms;
  
  unsigned seed;

  static FVector grads[8];
};

class Simplex : public Noise {
 public:
  Simplex(unsigned seed);

  float value(float x, float y) override;
  
  private:
  void calcPermutations();
  float dotGradient(int g[3], float x, float y);

  std::vector<unsigned> perms;
  
  unsigned seed;
  
  static int grads[12][3];
};