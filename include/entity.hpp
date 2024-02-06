#pragma once

#include "geom.hpp"

class Entity {
 public:
  Entity(IPoint pos);

  void setPosition(IPoint npos);
  void move(IVector dir);

  IPoint getPosition();

 private:
  IPoint position;
};
