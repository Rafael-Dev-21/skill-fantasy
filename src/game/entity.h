#ifndef ENTITY_H
#define ENTITY_H

#include "position.h"

struct Entity {
 public:
  Entity(Position pos);
  ~Entity();
  void move(Position next);

  Position pos;
};

#endif
