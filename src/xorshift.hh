#pragma once

#include <cstdint>

class XorShift {
public:
  XorShift(uint32_t state);
  uint32_t next();
  uint32_t prev();

private:
  uint32_t Ilshift(uint32_t x, uint32_t shift);
  uint32_t Irshift(uint32_t x, uint32_t shift);
  uint32_t state;
};
