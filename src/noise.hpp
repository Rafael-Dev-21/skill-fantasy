#pragma once



class Noise {
public:
	Noise();
	~Noise() = default;

	float value2d(float y, float x);
	float perlin2d(float y, float x);

	float value3d(float z, float y, float x);
	float perlin3d(float z, float y, float x);

private:

	int grad2d(int y, int x);

	float value2(float y, float x);

	float dot2(int grad, float y, float x);

	float perlin2(float y, float x);

	int grad3d(int z, int y, int x);
	
	float value3(float z, float y, float x);

	float dot3(int grad, float z, float y, float x);

	float perlin3(float z, float y, float x);

public:
	int m_seed = 0;
	float m_frequency = 1;
	float m_amplitude = 1;
	float m_persistence = 2;
	float m_lacunarity = 2;
	int m_octaves = 1;
};
