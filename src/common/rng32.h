#pragma once

#include <stdint.h>

static uint32_t _rng32_seed = 0x12345678;
static inline uint32_t
rng32(void)
{
  _rng32_seed ^= _rng32_seed << 13;
  _rng32_seed ^= _rng32_seed >> 17;
  _rng32_seed ^= _rng32_seed << 5;
  return _rng32_seed;
}
