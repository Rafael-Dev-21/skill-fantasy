#pragma once

#include <cmath>

namespace Math {
	float lerp(float a, float b, float t);
	float smooth(float t);
	float smoother(float t);
	float normalize(float value, float min, float max);

	template<typename T>
	static void shuffle(T * array, int size)
	{
		for (int e = size - 1; e > 0; e--) {
            float r = (rand() % 1000) / 1000.0;
            int index = (int)round(r * (e - 1));
			T temp = array[e];

			array[e] = array[index];
			array[index] = temp;
		}
	}
};


