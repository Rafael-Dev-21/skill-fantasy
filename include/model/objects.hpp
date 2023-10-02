#pragma once

#include <string>

struct LooseObject;

struct FixedObject {
  std::string name;
  int sprite;
  int colors;
  bool block = true;
};

struct LooseObject {
  std::string name;
  int quantity;
};