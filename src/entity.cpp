#include "entity.hpp"

Entity::Entity(IPoint pos):
  position(pos)
{}

void Entity::setPosition(IPoint npos) { 
  position = npos; 
}

void Entity::move(IVector dir) {
  position += dir;
}

IPoint Entity::getPosition() {
  return position;
}
