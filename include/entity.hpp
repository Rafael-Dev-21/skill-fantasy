#pragma once

#include "geom.hpp"

class Entity {
 public:
  Entity(IPoint pos, int sprite = '1', int colors = 1);

  void setPosition(IPoint npos);
  void move(IVector dir);
  void render(IVector cameraOrigin);

  IPoint getPosition();

 private:
  IPoint position;
  int sprite;
  int colors;
};
