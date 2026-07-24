#pragma once

#include "skfantasy.hpp"

namespace util {
static inline CreatureHandle copyCreature(World *w, Creature& c, Point p)
{
  if (creature_at(w, p) != nullptr)
    return HandleVector<Creature,Handle>::null_handle;
  Creature copy{};
  copy.position.x = p.x;
  copy.position.y = p.y;
  copy.color = c.color;
  copy.facing = c.facing;
  copy.glyph = c.glyph;
  copy.is_alive = c.is_alive;
  copy.is_flammable = c.is_flammable;
  for (int i = STAT_STR; i < STATS_COUNT; i++) {
    copy.stats[i].base = c.stats[i].base;
    copy.stats[i].modifier = c.stats[i].modifier;
  }
  auto ht = w->creatures.add(std::move(copy));
  if (ht == HandleVector<Creature,Handle>::null_handle) {
    return ht;
  }
  auto& stored = w->creatures.get(ht);
  stored.brain = c.brain->clone(w, ht);
  int idx = p.x + p.y * w->width;
  w->spatial_cache[idx] = ht;
  return ht;
}
};
