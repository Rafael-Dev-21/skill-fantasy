#ifndef ENTITY_H
#define ENTITY_H

#include "position.h"

typedef struct {
  Position pos;
  char ch;
  int color;
} Entity;

typedef Entity *EntityPtr;

EntityPtr createEntity(Position startPos, char ch, int color);
void freeEntity(EntityPtr entity);
void moveEntity(EntityPtr entity, Position newPos);

#endif
