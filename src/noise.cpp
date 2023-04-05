#include "noise.hpp"
#include "math.hpp"
#include <cmath>

static int hash[] = {
        151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36,
                      103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0,
                      26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56,
                      87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
                      77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
                      46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
                      187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109,
                      198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
                      255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183,
                      170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43,
                      172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112,
                      104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162,
                      241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106,
                      157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205,
                      93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
                      151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36,
                      103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0,
                      26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56,
                      87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
                      77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
                      46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
                      187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109,
                      198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
                      255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183,
                      170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43,
                      172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112,
                      104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162,
                      241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106,
                      157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205,
                      93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

Noise::Noise()
{}

float Noise::value2d(float y, float x)
{
	float ya = y * m_frequency;
	float xa = x * m_frequency;
	float amp = m_amplitude;
	float result = 0.0;
	float divider = 0;

	for (int i = 0; i < m_octaves; i++) {
		result += value2(ya, xa) * amp;
		divider += amp * 256;
		xa *= m_lacunarity;
		ya *= m_lacunarity;
		amp /= m_persistence;
	}

	return result / divider;
}

float Noise::perlin2d(float y, float x)
{
	float ya = y * m_frequency;
	float xa = x * m_frequency;
	float amp = m_amplitude;
	float result = 0.0;
	float divider = 0;

	for (int i = 0; i < m_octaves; i++) {
		result += perlin2(ya, xa) * amp;
		divider += amp;
		xa *= m_lacunarity;
		ya *= m_lacunarity;
		amp /= m_persistence;
	}

	return result / divider;
}

float Noise::value3d(float z, float y, float x)
{
	float za = z * m_frequency;
	float ya = y * m_frequency;
	float xa = x * m_frequency;
	float amp = m_amplitude;
	float result = 0.0;
	float divider = 0;

	for (int i = 0; i < m_octaves; i++) {
		result += value3(za, ya, xa) * amp;
		divider += amp * 256;
		za *= m_lacunarity;
		ya *= m_lacunarity;
		xa *= m_lacunarity;
		amp /= m_persistence;
	}

	return result / divider;
}

float Noise::perlin3d(float z, float y, float x)            {
        float za = z * m_frequency;
        float ya = y * m_frequency;                                float xa = x * m_frequency;                                float amp = m_amplitude;
        float result = 0.0;
        float divider = 0;

        for (int i = 0; i < m_octaves; i++) {
                result += perlin3(za, ya, xa) * amp;
                divider += amp * 256;
                za *= m_lacunarity;
                ya *= m_lacunarity;
                xa *= m_lacunarity;
                amp /= m_persistence;                              }
                                                                   return result / divider;
}

int Noise::grad2d(int y, int x)
{
	int yindex = (m_seed + y) % 256;
	if (yindex < 0)
		yindex += 255;
	int xindex = (m_seed + hash[yindex] + x) % 256;
	if (xindex < 0)
		xindex += 255;
	return hash[xindex];
}

float Noise::value2(float y, float x)
{
	int yint = (int) y;
	int xint = (int) x;

	float yfrac = y - yint;
	float xfrac = x - xint;

	int s = grad2d(yint, xint);
	int t = grad2d(yint, xint + 1);
	int u = grad2d(yint + 1, xint);
	int v = grad2d(yint + 1, xint + 1);

	float upper = smoothstep(s, t, xfrac);
	float lower = smoothstep(u, v, xfrac);

	return smoothstep(upper, lower, yfrac);
}

float Noise::dot2(int grad, float y, float x)
{
	switch(grad & 0x7) {
	case 0x0:
		return x;
	case 0x1:
		return x + y;
	case 0x2:
		return y;
	case 0x3:
		return -x + y;
	case 0x4:
		return -x;
	case 0x5:
		return -x - y;
	case 0x6:
		return -y;
	case 0x7:
		return x - y;
	default:
		return 0;
	}
}

float Noise::perlin2(float y, float x)
{
	int yint = (int) y;
	int xint = (int) x;

	float yfrac = y - yint;
	float xfrac = x - xint;

	int s = grad2d(yint, xint);
	int t = grad2d(yint, xint + 1);
	int u = grad2d(yint + 1, xint);
	int v = grad2d(yint + 1, xint + 1);

	float n0, n1, x0, x1, value;

	n0 = dot2(s, yfrac, xfrac);
	n1 = dot2(t, yfrac, xfrac - 1);
	x0 = smoothstep(n0, n1, xfrac);
	n0 = dot2(u, yfrac - 1, xfrac);
	n1 = dot2(v, yfrac - 1, xfrac - 1);
	x1 = smoothstep(n0, n1, xfrac);
	value = smoothstep(x0, x1, yfrac);

	return ((value * 1.7) + 1) * 0.5;
}

int Noise::grad3d(int z, int y, int x)
{
	int zindex = (m_seed + z) % 256;
	if (zindex < 0)
		zindex += 255;
	int yindex = (m_seed + hash[zindex] + y) % 256;
	if (yindex < 0)
		yindex += 255;
	int xindex = (m_seed + hash[yindex] + x) % 256;
	if (xindex < 0)
		xindex += 255;
	return hash[xindex];
}

float Noise::value3(float z, float y, float x)
{
	int zint = (int) z;
	int yint = (int) y;
	int xint = (int) x;

	float zfrac = z - zint;
	float yfrac = y - yint;
	float xfrac = x - xint;

	int aaa = grad3d(zint, yint, xint);
	int aab = grad3d(zint, yint, xint + 1);
	int aba = grad3d(zint, yint + 1, xint);
	int abb = grad3d(zint, yint + 1, xint + 1);
	int baa = grad3d(zint + 1, yint, xint);
        int bab = grad3d(zint + 1, yint, xint + 1);
        int bba = grad3d(zint + 1, yint + 1, xint);
        int bbb = grad3d(zint + 1, yint + 1, xint + 1);

	float x0, x1, y0, y1, value;

	x0 = smoothstep(aaa, aab, xfrac);
	x1 = smoothstep(aba, abb, xfrac);
	y0 = smoothstep(x0, x1, yfrac);
	x0 = smoothstep(baa, bab, xfrac);
	x1 = smoothstep(bba, bbb, xfrac);
	y1 = smoothstep(x0, x1, yfrac);
	value = smoothstep(y0, y1, zfrac);
	return value;
}

float Noise::dot3(int grad, float z, float y, float x)
{
	return ( x * (std::cosf(grad) + std::cosf(-grad)) + y * std::sinf(-grad) + z * (std::sinf(grad) + std::cosf(-grad)));
}

float Noise::perlin3(float z, float y, float x)
{
	int zint = (int) z;
	int yint = (int) y;
	int xint = (int) x;

	float zfrac = z - zint;
	float yfrac = y - yint;
	float xfrac = x - xint;

	int aaa = grad3d(zint, yint, xint);
        int aab = grad3d(zint, yint, xint + 1);                    int aba = grad3d(zint, yint + 1, xint);
        int abb = grad3d(zint, yint + 1, xint + 1);                int baa = grad3d(zint + 1, yint, xint);
        int bab = grad3d(zint + 1, yint, xint + 1);
        int bba = grad3d(zint + 1, yint + 1, xint);                int bbb = grad3d(zint + 1, yint + 1, xint + 1);

	return smoothstep(
			smoothstep(
				smoothstep(
					dot3(aaa, zfrac, yfrac, xfrac),
					dot3(aab, zfrac, yfrac, xfrac - 1),
					xfrac),
				smoothstep(
					dot3(aba, zfrac, yfrac - 1, xfrac),
					dot3(abb, zfrac, yfrac - 1, xfrac - 1),
					xfrac),
				yfrac),
			smoothstep(                                                        smoothstep(
                                        dot3(baa, zfrac - 1, yfrac, xfrac),
					dot3(bab, zfrac - 1, yfrac, xfrac - 1),
					xfrac),
                                smoothstep(
                                        dot3(bba, zfrac - 1, yfrac - 1, xfrac),
                                        dot3(bbb, zfrac - 1, yfrac - 1, xfrac - 1),
					xfrac),
				yfrac),
			zfrac);
}
