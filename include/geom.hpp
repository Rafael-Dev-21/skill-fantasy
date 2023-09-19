#pragma once

#include <cmath>

template <typename T>
struct Vector;

template <typename T>
struct Point {
  Point(T x = 0, T y = 0) : x(x), y(y) {}

  // math methods

  Point<T> add(Vector<T> const& vec) { return clone().addMe(vec); }
  Point<T> addMe(Vector<T> const& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
  }
  Vector<T> sub(Point<T> const& p) { return Vector<T>(x - p.x, y - p.y); }

  // operators

  inline Point<T> operator+(Vector<T> const& vec) { return add(vec); }
  inline Point<T> operator+=(Vector<T> const& vec) { return addMe(vec); }

  inline Vector<T> operator-(Point<T> const& p) { return sub(p); }

  // misc methods

  Point<T> clone() { return Point<T>(x, y); }

  T x;
  T y;
};

using IPoint = Point<int>;
using DPoint = Point<double>;
using FPoint = Point<float>;
template <typename T>
using PPoint = Point<Point<T>>;

template <typename T>
struct Vector {
  Vector(T x = 0, T y = 0) : x(x), y(y) {}

  // scalar methods

  T length() { return (T)sqrt(x * x + y * y); }
  double angle() { return -atan2(-y, x); }

  // math methods

  Vector<T> add(Vector<T> const& vec) { return clone().addMe(vec); }
  Vector<T> addMe(Vector<T> const& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
  }
  Vector<T> sub(Vector<T> const& vec) { return clone().subMe(vec); }
  Vector<T> subMe(Vector<T> const& vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
  }
  Vector<T> mul(T const& scalar) { return clone().mulMe(scalar); }
  Vector<T> mulMe(T const& scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }
  Vector<T> div(T const& scalar) { return clone().divMe(scalar); }
  Vector<T> divMe(T const& scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }
  Vector<T> negate() { return Vector<T>(-x, -y); }

  Vector<T> norm() { return clone().normMe(); }

  Vector<T> normMe() {
    if (length() != 0) return divMe(length());
    return *this;
  }

  inline static T dot(Vector<T> const& left, Vector<T> const& right) {
    return (left.x * right.x + left.y * right.y);
  }

  // operators

  inline Vector<T> operator+(Vector<T> const& vec) { return add(vec); }
  inline Vector<T> operator+=(Vector<T> const& vec) { return addMe(vec); }
  inline Vector<T> operator-(Vector<T> const& vec) { return sub(vec); }
  inline Vector<T> operator-=(Vector<T> const& vec) { return subMe(vec); }
  inline Vector<T> operator*(T const& scalar) { return mul(scalar); }
  inline Vector<T> operator*=(T const& scalar) { return mulMe(scalar); }
  inline Vector<T> operator/(T const& scalar) { return div(scalar); }
  inline Vector<T> operator/=(T const& scalar) { return divMe(scalar); }
  inline Vector<T> operator-() { return negate(); }

  // misc methods
  Vector<T> clone() { return Vector<T>(x, y); }

  T x;
  T y;
};

using IVector = Vector<int>;
using DVector = Vector<double>;
using FVector = Vector<float>;
template <typename T>
using VVector = Vector<Vector<T>>;
