#pragma once
#include <entt/entt.hpp>
#include <vector>
#include "components.hpp"
#include "types.hpp"

struct Tile {
  TileId type{TileId::None};
  ObjectId object{ObjectId::None};
  int growtime{0};
};

class World {
public:
  World(int width, int height);

  void init(long seed);
  int update(entt::entity player);

  Tile& tile_at(Point p);
  const Tile& tile_at(Point p) const;
  bool in_bounds(Point p) const;

  entt::entity creature_at(Point p) const;
  bool is_solid(Point p) const;
  bool is_flammable(Point p) const;

  void place_wall(Point p);
  void break_wall(Point p);
  void try_toil(Point p);

  const Point random_empty_point() const;

  int width() const { return width_; }
  int height() const { return height_; }
  entt::registry& registry() { return reg_; }
  const entt::registry& registry() const { return reg_; }

private:
  int width_;
  int height_;
  entt::registry reg_;
  std::vector<Tile> tiles_;
  std::vector<entt::entity> spatial_cache_;

  std::vector<int> moist_buf1_, moist_buf2_;
  int current_moist_buf_{0};
};
