#pragma once
#include <cstdint>
#include <compare>

enum class Direction : uint8_t {
  Up, Right, Down, Left
};

enum class StatId : uint8_t {
  Str, Mbl, Mnd, Fth, Hrt, Count
};

enum class TileId : uint8_t {
  None, Grass, Sand, Water, Stone, Soil, Mud, Count
};

enum class ObjectId : uint8_t {
  None, Wall, Bush, WheatSeed, Wheat, Count
};

struct Stat {
  int8_t base{0};
  int8_t modifier{0};
};

struct Point {
  int16_t x{0};
  int16_t y{0};

  auto operator<=>(const Point&) const = default;

  constexpr Point operator+(const Point& o) const
  {
    return {static_cast<int16_t>(x+o.x), static_cast<int16_t>(y+o.y)};
  }
};

constexpr Point dir_to_point(Direction dir)
{
  switch (dir) {
    case Direction::Up:    return {0, -1};
    case Direction::Down:  return {0,  1};
    case Direction::Left:  return {-1, 0};
    case Direction::Right: return {1,  0};
  }
  return {0, 0};
}
