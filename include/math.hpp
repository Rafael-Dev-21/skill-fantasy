#pragma once

#include <cmath>
#include <cstdlib>

namespace Math {
float lerp(float a, float b, float t);
float smooth(float t);
float smoother(float t);
float normalize(float value, float min, float max);
float hash(int x, int y);

template <typename T>
static void shuffle(T* array, int size) {
  for (int e = size - 1; e > 0; e--) {
    int index = rand() % e;
    T temp = array[e];

    array[e] = array[index];
    array[index] = temp;
  }
}
};  // namespace Math
