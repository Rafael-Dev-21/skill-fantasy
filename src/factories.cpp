#include <entt/entt.hpp>
#include "factories.hpp"
#include "world.hpp"
#include "components.hpp"
#include "types.hpp"

static inline uint32_t colorpack(uint8_t r, uint8_t g, uint8_t b)
{
  return (r<<16) | (g<<8) | b;
}

static inline std::array<Stat, static_cast<size_t>(StatId::Count)> generate_player_stats()
{}
static inline std::array<Stat, static_cast<size_t>(StatId::Count)> generate_bat_stats()
{}
static inline std::array<Stat, static_cast<size_t>(StatId::Count)> generate_fungi_stats()
{}
static inline std::array<Stat, static_cast<size_t>(StatId::Count)> generate_fire_stats()
{}

entt::entity make_player(World& world)
{
  auto& reg = world.registry();
  auto e = reg.create();

  reg.emplace<Position>(e, world.random_empty_point());
  reg.emplace<Facing>(e, Direction::Up);
  reg.emplace<Renderable>(e, '@', colorpack(210, 210, 50));
  reg.emplace<Stats>(e, generate_player_stats());
  reg.emplace<Flammable>(e);
  reg.emplace<Alive>(e);
  reg.emplace<PlayerTag>(e);
  return e;
}

entt::entity make_bat(World& world)
{
  auto& reg = world.registry();
  auto e = reg.create();

  reg.emplace<Position>(e, world.random_empty_point());
  reg.emplace<Facing>(e, Direction::Up);
  reg.emplace<Renderable>(e, '@', colorpack(210, 210, 50));
  reg.emplace<Stats>(e, generate_player_stats());
  reg.emplace<Flammable>(e);
  reg.emplace<Alive>(e);
  reg.emplace<BatTag>(e);
  return e;
}
entt::entity make_fungi(World& world)
{ 
  auto& reg = world.registry();
  auto e = reg.create();

  reg.emplace<Position>(e, world.random_empty_point());
  reg.emplace<Facing>(e, Direction::Up);
  reg.emplace<Renderable>(e, '@', colorpack(15, 135, 25));
  reg.emplace<Stats>(e, generate_fungi_stats());
  reg.emplace<Flammable>(e);
  reg.emplace<Alive>(e);
  reg.emplace<FungiBrain>(e, 0);
  return e;
}
entt::entity make_fire(World& world, Point cell)
{
  if (!world.in_bounds(cell))
    return entt::null;
  if (!world.is_flammable(cell))
    return entt::null;
  auto& reg = world.registry();
  auto e = reg.create();

  reg.emplace<Position>(e, cell);
  reg.emplace<Facing>(e, Direction::Up);
  reg.emplace<Renderable>(e, '@', colorpack(15, 135, 25));
  reg.emplace<Stats>(e, generate_fire_stats());
  reg.emplace<Alive>(e);
  reg.emplace<FireBrain>(e, 0);
  return e;
}
