#include "noise.hpp"
#include "math.hpp"

#include <cmath>

float Noise::fbm(float x, float y, FBMParams params)
{
	float result = 0.0, divider = 0.0;
	float freq = params.frequency;
	float amp = params.amplitude;

	for (int i = 0; i < params.octaves; i++) {
		divider += amp;
		result += amp * value(x * freq, y * freq);
		freq *= params.lacunarity;
		freq *= params.persistence;
	}
	if (divider == 0)
        return result;
    return result / divider;
}

Perlin::Perlin()
{
	calcPermutations();
}

std::vector<FVector> Perlin::grads = {
	FVector(0, -1),
	FVector(1, -1),
	FVector(1, 0),
	FVector(1, 1),
	FVector(0, 1),
	FVector(-1, 1),
	FVector(-1, 0),
	FVector(-1, -1)
};

float Perlin::value(float x, float y)
{
	using namespace Math;

	int ix = (int)floor(abs(x)) & 255;
	int iy = (int)floor(abs(y)) & 255;

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

void Perlin::calcPermutations()
{
	using namespace Math;

	for (int i = 0; i < 256; i++)
		perms[i] = i;

	shuffle(perms, 256);

	for (int i = 0; i < 256; i++)
		perms[i + 256] = perms[i];
}

float Perlin::dotGradient(int hash, float x, float y)
{
	auto gradient = grads[hash % 0x7];

	return FVector::dot(FVector(x, y), gradient);
}
