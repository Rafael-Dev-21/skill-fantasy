#include <noise.hpp>

#include <iostream>

int main(void)
{
	int x;
	float total = 0, max = -INFINITY, min = INFINITY;

	float width = 1024;
	float height = 1024;

	Perlin noise;

	std::cout << "proccesssing..." << std::endl;
	for (x = 0; x < width; x++) {
		int y;
		float parcial = 0;
		for (y = 0; y < height; y++) {
			float n = noise.value(x / 512.0 - 0.5, y / 512.0 - 0.5);
			if (n > max) max = n;
			if (n < min) min = n;

			parcial += n;
		}
		total += parcial / y;
	}

	total /= x;

	std::cout << (int)(width * height) << " samples" << std::endl;

	std::cout << "max: " << max << std::endl;
	std::cout << "min: " << min << std::endl;
	std::cout << "avg: " << total << std::endl;

	return 0;
}
