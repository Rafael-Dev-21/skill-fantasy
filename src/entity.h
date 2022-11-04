#ifndef ENTITY_H
#define ENTITY_H

#include "position.h"

struct Entity {
public:
  Entity(Position pos, char ch, int color);
  ~Entity();
  void move(Position next);

  Position pos;
  char ch;
  int color;
};

#endif
