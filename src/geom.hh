#pragma once

#include <vector>
#include <cassert>

struct Pt {
  Pt(int x=0) :
    x(x), y(x)
  {}
  Pt(int x, int y) :
    x(x), y(y)
  {}

  Pt& operator+=(const Pt& p)
  {
    x += p.x;
    y += p.y;
    return *this;
  }
  Pt operator+(const Pt& p)
  {
    return Pt{x + p.x, y + p.y};
  }
  Pt& operator-=(const Pt& p)
  {
    x -= p.x;
    y -= p.y;
    return *this;
  }
  Pt operator-(const Pt& p)
  {
    return Pt{x - p.x, y - p.y};
  }

  int x;
  int y;
};

template<typename T>
class Grid2 {
public:
  Grid2(int w, int h) :
    width_(w), height_(h)
  {
    assert(("width should be greater than zero." && w > 0));
    assert(("height should be greater than zero." && h > 0));
    items_.resize(w * h);
  }

  T& get(int x, int y)
  {
    INVARIANT(x, y);
    return items_[x + y * width_];
  }

  T& get(const Pt& p)
  {
    return get(p.x, p.y);
  }

  void set(int x, int y, const T& item)
  {
    INVARIANT(x, y);
    items_[x + y * width_] = item;
  }

  void set(const Pt& p, const T& item)
  {
    set(p.x, p.y, item);
  }

  T* operator[](int y)
  {
    INVARIANT(0, y);
    return &items_[y * width_];
  }

  T& operator[](const Pt& p)
  {
    return get(p);
  }

  int width() { return width_; }
  int height() { return height_; }
  int size() { return width_ * height_; }

private:
  void INVARIANT(int x, int y)
  {
    assert(("x should not be less than zero." && x >= 0));
    assert(("y should not be less than zero." && y >= 0));
    assert(("x should be less than width." && x < width_));
    assert(("y should be less than height." && y < height_));
  }

  std::vector<T> items_;
  int width_;
  int height_;
};
