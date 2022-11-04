#include "common.h"
#include "entity.h"

Entity::Entity(Position pos, char ch, int color)
    : pos(pos), ch(ch), color(color) {}

Entity::~Entity() = default;

void Entity::move(Position next) {
  pos.y = next.y;
  pos.x = next.x;
}
