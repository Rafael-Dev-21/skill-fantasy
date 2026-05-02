#pragma once

#include <inttypes.h>
#include "skfantasy.h"

typedef uint16_t CreatureKindId;
typedef uint32_t CreatureId;

typedef struct CreatureKind CreatureKind;

struct CreatureKind {
  const char *name;

  int glyph;
  int color;

  Stat base_stats[STAT_COUNT];

  void (*enter)(World*, CreatureId, Point, TileId);
  void (*tick)(World*, CreatureId);
  void (*bump)(World*, CreatureId, CreatureId);
  void (*notify)(World*, char *msg);
};
