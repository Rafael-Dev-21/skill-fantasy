#pragma once

#include <string>

struct FixedObject {
  std::string name;
  int sprite;
  int colors;
  bool block = true;
};

struct LooseObject {};