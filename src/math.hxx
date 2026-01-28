#pragma once

template<typename T>
static inline constexpr T clamp(T val, T mn, T mx) { return (val < mn) ? mn : ((val > mx) ? mx : val); }

template<typename T>
static inline constexpr T lerp(T a, T b, double t)
{
  if (t < 0.)
    return a;
  if (t > 1.)
    return b;
  return static_cast<T>(a * (1.-t) + b * t);
}

static inline constexpr double fade(double t)
{
  return t * t * t * (t * (t * 6 - 15) + 10);
}
