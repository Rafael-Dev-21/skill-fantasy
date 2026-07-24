#pragma once
#include <entt/entt.hpp>
#include "types.hpp"

struct Renderable {
  uint32_t glyph{};
  uint32_t color{};
};

struct Flammable {};
struct Alive {};

struct Position {
  Point p;
};

struct Facing {
  Direction dir{Direction::Up};
};

struct Stats {
  std::array<Stat, static_cast<size_t>(StatId::Count)> stats{};

  int8_t get(StatId id) const;
  int8_t get_base(StatId id) const;
  void apply(StatId id, int8_t mod);
};

struct PlayerTag {};
struct BatTag {};
struct FungiBrain { int spread_count{0}; };
struct FireBrain { int spread_count{0}; };
