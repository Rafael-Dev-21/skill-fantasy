#include "xorshift.hh"

XorShift::XorShift(uint32_t state) :
  state(state)
{}

uint32_t XorShift::next()
{
  state ^= state << 13;
  state ^= state >> 17;
  state ^= state << 5;
  return state;
}

uint32_t XorShift::prev()
{
  state = Ilshift(state, 5);
  state = Irshift(state, 17);
  state = Ilshift(state, 13);
  return state;
}

uint32_t XorShift::Ilshift(uint32_t x, uint32_t shift)
{
  uint32_t res = x;
  for (int i = 0; i < 32 / shift; i++)
    res = x ^ (res << shift);
  return res;
}
uint32_t XorShift::Irshift(uint32_t x, uint32_t shift)
{
  uint32_t res = x;
  for (int i = 0; i < 32 / shift; i++)
    res = x ^ (res >> shift);
  return res;
}
