#include "entity.h"

Entity::Entity(Position pos) : pos(pos) {}

Entity::~Entity() = default;

void Entity::move(Position next) {
  pos.y = next.y;
  pos.x = next.x;
}
