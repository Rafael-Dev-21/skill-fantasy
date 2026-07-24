#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <entt/entt.hpp>
#include <iostream>

#include "privdefs.h"
#include "handlevector.hh"

struct Brain {
  explicit Brain(World *world, Handle creature) :
    world(world), creature(creature)
  {}

  virtual ~Brain() = default;

  virtual void enter(Point p) {}
	virtual void update() {}
  virtual std::unique_ptr<Brain> clone(World *w, Handle ht) = 0;

  World *world;
  Handle creature;
};

using CreatureHandle = Handle;

constexpr static inline uint32_t colorpack(uint8_t r, uint8_t g, uint8_t b)
{
  return (r << 16) | (g << 8) | b;
}

static inline ftxui::Color colorupack(uint32_t color) 
{
  return ftxui::Color::RGB((color>>16)&255, (color>>8)&255, color&255);
}

struct Creature {
  Handle handle{};
	Stat stats[STATS_COUNT]{};
  std::unique_ptr<Brain> brain;
	Point position{};
	Direction facing{};
	uint32_t glyph{};
  uint32_t color{};
  bool is_flammable{};
  bool is_alive{};
};

struct World {
	int16_t width;
	int16_t height;
  std::vector<Tile> tiles;
  HandleVector<Creature, CreatureHandle> creatures;
  std::vector<int> moisture_buffer1;
  std::vector<int> moisture_buffer2;
  int current_moisture_buffer;
  std::vector<CreatureHandle> spatial_cache;
};

struct PlayerBrain: public Brain {
  PlayerBrain(World *world, CreatureHandle creature) :
    Brain(world, creature)
  {}
  virtual ~PlayerBrain() = default;

  virtual void enter(Point p) override;
  virtual void update() override;
  virtual std::unique_ptr<Brain> clone(World *w, Handle ht) override
  {
    return std::make_unique<PlayerBrain>(w, ht);
  }
};
struct FungiBrain: public Brain {
  FungiBrain(World *world, CreatureHandle creature) :
    Brain(world, creature)
  {}
  virtual ~FungiBrain() = default;

  virtual void enter(Point p) override;
  virtual void update() override;
  int spread_count{0};
private:
  void spread();
  virtual std::unique_ptr<Brain> clone(World *w, Handle ht) override
  {
    auto r = std::make_unique<FungiBrain>(w, ht);
    r->spread_count = spread_count;
    return std::move(r);
  }
};
struct BatBrain: public Brain {
  BatBrain(World *world, CreatureHandle creature) :
    Brain(world, creature)
  {}
  virtual ~BatBrain() = default;

  virtual void enter(Point p) override;
  virtual void update() override;
  virtual std::unique_ptr<Brain> clone(World *w, Handle ht) override
  {
    return std::make_unique<BatBrain>(w, ht);
  }
};
struct FireBrain: public Brain {
  FireBrain(World *world, CreatureHandle creature) :
    Brain(world, creature)
  {}
  virtual ~FireBrain() = default;

  virtual void enter(Point p) override;
  virtual void update() override;
  int spread_count{0};
  
  virtual std::unique_ptr<Brain> clone(World *w, Handle ht) override
  {
    auto r = std::make_unique<FireBrain>(w, ht);
    r->spread_count = spread_count;
    return std::move(r);
  }

  private:
  void spread();
};

Creature create_creature(Brain *brain);

struct CreatureFactory {
  CreatureHandle makePlayer();
  CreatureHandle makeBat();
  CreatureHandle makeFungi();
  CreatureHandle makeFire(Point p);

  explicit CreatureFactory(World* world) :
    world(world)
  {} 
  World* world;
};


CreatureHandle add_creature_rand_empty(World *world, Creature&& creature);
void world_remove(World *world, CreatureHandle creature);
int world_update(World *world, CreatureHandle player);
