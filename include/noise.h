#ifndef NOISE_H
#define NOISE_H

typedef struct {
	float frequency;
	float amplitude;
	float lacunarity;
	float persistence;
	int octaves;
	float (*noisefn)(float, float);
} FBMParams;

// noise
float value2d(float x, float y);
float perlin2d(float x, float y);
float simplex2d(float x, float y);
float fbm2d(float x, float y, FBMParams params);

extern FBMParams default_fbm;

#endif
