# 1 "src/noise.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 388 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "src/noise.c" 2
# 1 "/data/data/com.termux/files/home/projetos/skill-fantasy/include/noise.h" 1




float lerp(float x, float y, float s);
float noise2d(float x, float y);
float fbm(float x, float y, float freq, int depth);
# 2 "src/noise.c" 2
# 1 "/data/data/com.termux/files/home/projetos/skill-fantasy/include/position.h" 1



struct position {
  int y;
  int x;
};
# 3 "src/noise.c" 2
# 1 "/data/data/com.termux/files/usr/include/math.h" 1 3 4
# 18 "/data/data/com.termux/files/usr/include/math.h" 3 4
# 1 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 1 3 4
# 372 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
# 1 "/data/data/com.termux/files/usr/include/android/versioning.h" 1 3 4
# 373 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 2 3 4
# 1 "/data/data/com.termux/files/usr/include/android/api-level.h" 1 3 4
# 185 "/data/data/com.termux/files/usr/include/android/api-level.h" 3 4
int android_get_application_target_sdk_version() __attribute__((__availability__(android,strict,introduced=24)));







# 1 "/data/data/com.termux/files/usr/include/bits/get_device_api_level_inlines.h" 1 3 4
# 38 "/data/data/com.termux/files/usr/include/bits/get_device_api_level_inlines.h" 3 4
int __system_property_get(const char* __name, char* __value);
int atoi(const char* __s) __attribute__((__pure__));

static __inline int android_get_device_api_level() {
  char value[92] = { 0 };
  if (__system_property_get("ro.build.version.sdk", value) < 1) return -1;
  int api_level = atoi(value);
  return (api_level > 0) ? api_level : -1;
}
# 194 "/data/data/com.termux/files/usr/include/android/api-level.h" 2 3 4
# 374 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 2 3 4

# 1 "/data/data/com.termux/files/usr/include/android/ndk-version.h" 1 3 4
# 376 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 2 3 4
# 19 "/data/data/com.termux/files/usr/include/math.h" 2 3 4
# 1 "/data/data/com.termux/files/usr/lib/clang/15.0.3/include/limits.h" 1 3 4
# 21 "/data/data/com.termux/files/usr/lib/clang/15.0.3/include/limits.h" 3 4
# 1 "/data/data/com.termux/files/usr/include/limits.h" 1 3 4
# 41 "/data/data/com.termux/files/usr/include/limits.h" 3 4
# 1 "/data/data/com.termux/files/usr/lib/clang/15.0.3/include/float.h" 1 3 4
# 42 "/data/data/com.termux/files/usr/include/limits.h" 2 3 4

# 1 "/data/data/com.termux/files/usr/include/linux/limits.h" 1 3 4
# 44 "/data/data/com.termux/files/usr/include/limits.h" 2 3 4
# 140 "/data/data/com.termux/files/usr/include/limits.h" 3 4
# 1 "/data/data/com.termux/files/usr/include/bits/posix_limits.h" 1 3 4
# 141 "/data/data/com.termux/files/usr/include/limits.h" 2 3 4
# 22 "/data/data/com.termux/files/usr/lib/clang/15.0.3/include/limits.h" 2 3 4
# 20 "/data/data/com.termux/files/usr/include/math.h" 2 3 4





typedef double __double_t;
typedef __double_t double_t;
typedef float __float_t;
typedef __float_t float_t;
# 76 "/data/data/com.termux/files/usr/include/math.h" 3 4
double acos(double __x);
float acosf(float __x);
long double acosl(long double __x) __asm__("acos") __attribute__((__availability__(android,strict,introduced=3)));

double asin(double __x);
float asinf(float __x);
long double asinl(long double __x) __asm__("asin") __attribute__((__availability__(android,strict,introduced=3)));

double atan(double __x);
float atanf(float __x);
long double atanl(long double __x) __asm__("atan") __attribute__((__availability__(android,strict,introduced=3)));

double atan2(double __y, double __x);
float atan2f(float __y, float __x);
long double atan2l(long double __y, long double __x) __asm__("atan2") __attribute__((__availability__(android,strict,introduced=3)));

double cos(double __x);
float cosf(float __x);
long double cosl(long double __x) __asm__("cos") __attribute__((__availability__(android,strict,introduced=3)));

double sin(double __x);
float sinf(float __x);
long double sinl(long double __x) __asm__("sin") __attribute__((__availability__(android,strict,introduced=3)));

double tan(double __x);
float tanf(float __x);
long double tanl(long double __x) __asm__("tan") __attribute__((__availability__(android,strict,introduced=3)));

double acosh(double __x);
float acoshf(float __x);
long double acoshl(long double __x) __asm__("acosh") __attribute__((__availability__(android,strict,introduced=3)));

double asinh(double __x);
float asinhf(float __x);
long double asinhl(long double __x) __asm__("asinh") __attribute__((__availability__(android,strict,introduced=3)));

double atanh(double __x);
float atanhf(float __x);
long double atanhl(long double __x) __asm__("atanh") __attribute__((__availability__(android,strict,introduced=3)));

double cosh(double __x);
float coshf(float __x);
long double coshl(long double __x) __asm__("cosh") __attribute__((__availability__(android,strict,introduced=3)));

double sinh(double __x);
float sinhf(float __x);
long double sinhl(long double __x) __asm__("sinh") __attribute__((__availability__(android,strict,introduced=3)));

double tanh(double __x);
float tanhf(float __x);
long double tanhl(long double __x) __asm__("tanh") __attribute__((__availability__(android,strict,introduced=3)));

double exp(double __x);
float expf(float __x);
long double expl(long double __x) __asm__("exp") __attribute__((__availability__(android,strict,introduced=3)));

double exp2(double __x);
float exp2f(float __x);
long double exp2l(long double __x) __asm__("exp2") __attribute__((__availability__(android,strict,introduced=3)));

double expm1(double __x);
float expm1f(float __x);
long double expm1l(long double __x) __asm__("expm1") __attribute__((__availability__(android,strict,introduced=3)));

double frexp(double __x, int* __exponent);
float frexpf(float __x, int* __exponent);
long double frexpl(long double __x, int* __exponent) __asm__("frexp") __attribute__((__availability__(android,strict,introduced=3)));

int ilogb(double __x) __attribute__((__const__));
int ilogbf(float __x) __attribute__((__const__));
int ilogbl(long double __x) __asm__("ilogb") __attribute__((__availability__(android,strict,introduced=3))) __attribute__((__const__));

double ldexp(double __x, int __exponent);
float ldexpf(float __x, int __exponent);
long double ldexpl(long double __x, int __exponent) __asm__("ldexp") __attribute__((__availability__(android,strict,introduced=3)));

double log(double __x);
float logf(float __x);
long double logl(long double __x) __asm__("log") __attribute__((__availability__(android,strict,introduced=3)));

double log10(double __x);
float log10f(float __x);
long double log10l(long double __x) __asm__("log10") __attribute__((__availability__(android,strict,introduced=3)));

double log1p(double __x);
float log1pf(float __x);
long double log1pl(long double __x) __asm__("log1p") __attribute__((__availability__(android,strict,introduced=3)));



double log2(double __x) __attribute__((__availability__(android,strict,introduced=18)));
float log2f(float __x) __attribute__((__availability__(android,strict,introduced=18)));
long double log2l(long double __x) __asm__("log2") __attribute__((__availability__(android,strict,introduced=18)));



double logb(double __x);
float logbf(float __x);
long double logbl(long double __x) __asm__("logb") __attribute__((__availability__(android,strict,introduced=3)));

double modf(double __x, double* __integral_part);
float modff(float __x, float* __integral_part);
long double modfl(long double __x, long double* __integral_part) __asm__("modf") __attribute__((__availability__(android,strict,introduced=3)));

double scalbn(double __x, int __exponent);
float scalbnf(float __x, int __exponent);
long double scalbnl(long double __x, int __exponent) __asm__("scalbn") __attribute__((__availability__(android,strict,introduced=3)));


double scalbln(double __x, long __exponent) ;
float scalblnf(float __x, long __exponent) ;
long double scalblnl(long double __x, long __exponent) ;

double cbrt(double __x);
float cbrtf(float __x);
long double cbrtl(long double __x) __asm__("cbrt") __attribute__((__availability__(android,strict,introduced=3)));

double fabs(double __x) __attribute__((__const__));
float fabsf(float __x) __attribute__((__const__));
long double fabsl(long double __x) __asm__("fabs") __attribute__((__availability__(android,strict,introduced=3))) __attribute__((__const__));

double hypot(double __x, double __y);
float hypotf(float __x, float __y);
long double hypotl(long double __x, long double __y) __asm__("hypot") __attribute__((__availability__(android,strict,introduced=3)));

double pow(double __x, double __y);
float powf(float __x, float __y);
long double powl(long double __x, long double __y) __asm__("pow") __attribute__((__availability__(android,strict,introduced=3)));

double sqrt(double __x);
float sqrtf(float __x);
long double sqrtl(long double __x) __asm__("sqrt") __attribute__((__availability__(android,strict,introduced=3)));

double erf(double __x);
float erff(float __x);
long double erfl(long double __x) __asm__("erf") __attribute__((__availability__(android,strict,introduced=3)));

double erfc(double __x);
float erfcf(float __x);
long double erfcl(long double __x) __asm__("erfc") __attribute__((__availability__(android,strict,introduced=3)));

double lgamma(double __x);
float lgammaf(float __x);
long double lgammal(long double __x) __asm__("lgamma") __attribute__((__availability__(android,strict,introduced=3)));

double tgamma(double __x);
float tgammaf(float __x);
long double tgammal(long double __x) __asm__("tgamma") __attribute__((__availability__(android,strict,introduced=3)));

double ceil(double __x);
float ceilf(float __x);
long double ceill(long double __x) __asm__("ceil") __attribute__((__availability__(android,strict,introduced=3)));

double floor(double __x);
float floorf(float __x);
long double floorl(long double __x) __asm__("floor") __attribute__((__availability__(android,strict,introduced=3)));

double nearbyint(double __x);
float nearbyintf(float __x);
long double nearbyintl(long double __x) __asm__("nearbyint") __attribute__((__availability__(android,strict,introduced=3)));

double rint(double __x);
float rintf(float __x);
long double rintl(long double __x) __asm__("rint") __attribute__((__availability__(android,strict,introduced=3)));

long lrint(double __x);
long lrintf(float __x);
long lrintl(long double __x) __asm__("lrint") __attribute__((__availability__(android,strict,introduced=3)));

long long llrint(double __x);
long long llrintf(float __x);
long long llrintl(long double __x) __asm__("llrint") __attribute__((__availability__(android,strict,introduced=3)));

double round(double __x);
float roundf(float __x);
long double roundl(long double __x) __asm__("roundl") __attribute__((__availability__(android,strict,introduced=3)));

long lround(double __x);
long lroundf(float __x);
long lroundl(long double __x) __asm__("lround") __attribute__((__availability__(android,strict,introduced=3)));

long long llround(double __x);
long long llroundf(float __x);
long long llroundl(long double __x) __asm__("llround") __attribute__((__availability__(android,strict,introduced=3)));

double trunc(double __x);
float truncf(float __x);
long double truncl(long double __x) __asm__("trunc") __attribute__((__availability__(android,strict,introduced=3)));

double fmod(double __x, double __y);
float fmodf(float __x, float __y);
long double fmodl(long double __x, long double __y) __asm__("fmod") __attribute__((__availability__(android,strict,introduced=3)));

double remainder(double __x, double __y);
float remainderf(float __x, float __y);
long double remainderl(long double __x, long double __y) __asm__("remainder") __attribute__((__availability__(android,strict,introduced=3)));

double remquo(double __x, double __y, int* __quotient_bits);
float remquof(float __x, float __y, int* __quotient_bits);
long double remquol(long double __x, long double __y, int* __quotient_bits) __asm__("remquo") __attribute__((__availability__(android,strict,introduced=3)));

double copysign(double __value, double __sign) __attribute__((__const__));
float copysignf(float __value, float __sign) __attribute__((__const__));
long double copysignl(long double __value, long double __sign) __asm__("copysign") __attribute__((__availability__(android,strict,introduced=3))) __attribute__((__const__));

double nan(const char* __kind) __attribute__((__const__));
float nanf(const char* __kind) __attribute__((__const__));
long double nanl(const char* __kind) __asm__("nan") __attribute__((__availability__(android,strict,introduced=13))) __attribute__((__const__));

double nextafter(double __x, double __y);
float nextafterf(float __x, float __y);
long double nextafterl(long double __x, long double __y) __asm__("nextafter") ;

double nexttoward(double __x, long double __y) ;
float nexttowardf(float __x, long double __y);
long double nexttowardl(long double __x, long double __y) __asm__("nexttoward") ;

double fdim(double __x, double __y);
float fdimf(float __x, float __y);
long double fdiml(long double __x, long double __y) __asm__("fdim") __attribute__((__availability__(android,strict,introduced=3)));

double fmax(double __x, double __y) __attribute__((__const__));
float fmaxf(float __x, float __y) __attribute__((__const__));
long double fmaxl(long double __x, long double __y) __asm__("fmax") __attribute__((__availability__(android,strict,introduced=3))) __attribute__((__const__));

double fmin(double __x, double __y) __attribute__((__const__));
float fminf(float __x, float __y) __attribute__((__const__));
long double fminl(long double __x, long double __y) __asm__("fmin") __attribute__((__availability__(android,strict,introduced=3))) __attribute__((__const__));

double fma(double __x, double __y, double __z);
float fmaf(float __x, float __y, float __z);
long double fmal(long double __x, long double __y, long double __z) __asm__("fma") ;
# 329 "/data/data/com.termux/files/usr/include/math.h" 3 4
int (isinf)(double __x) __attribute__((__const__)) __attribute__((__availability__(android,strict,introduced=21)));


int (isnan)(double __x) __attribute__((__const__));



extern int signgam;

double j0(double __x);
double j1(double __x);
double jn(int __n, double __x);
double y0(double __x);
double y1(double __x);
double yn(int __n, double __x);
# 4 "src/noise.c" 2

static int p[] = { 151,160,137,91,90,15,
   131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
   190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
   88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
   77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
   102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
   135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
   5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
   223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
   129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
   251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
   49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
   138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
   151,160,137,91,90,15, 131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23, 190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33, 88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166, 77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244, 102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196, 135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123, 5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42, 223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9, 129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228, 251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107, 49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254, 138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

static struct position grads[] = {
 { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 },
 { -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }};


float lerp(float x, float y, float s)
{
 return x + s * (y - x);
}

static float fade(float t)
{
 return t * t * t * (t * (t * 6 - 15) + 10);
}

static float grad(int hash, float x, float y)
{
 return grads[hash].x * x + grads[hash].y * y;
}

float noise2d(float x, float y)
{
 int
  ix = (int)floor(x),
  iy = (int)floor(y);

 x = x - ix;
 y = y - iy;

 float
  fx = fade(x),
  fy = fade(y);

 ix &= 255;
 iy &= 255;

 int
  g1 = p[ix + p[iy]],
  g2 = p[ix + 1 + p[iy]],
  g3 = p[ix + p[iy + 1]],
  g4 = p[ix + 1 + p[iy + 1]];

 float
  n1 = grad(g1 & 7, x, y),
  n2 = grad(g2 & 7, x - 1, y),
  n3 = grad(g3 & 7, x, y - 1),
  n4 = grad(g4 & 7, x - 1, y - 1);

 float
  y1 = lerp(n1, n2, fx),
  y2 = lerp(n3, n4, fx);

 return (lerp(y1, y2, fy) + 1) / 2;
}

float fbm(float x, float y, float freq, int depth)
{
 float xa = x * freq;
 float ya = y * freq;
 float amp = 1.0;
 float fin = 0;
 float div = 0.0;

 int i;
 for (i = 0; i < depth; i++) {
  div += amp;
      fin += noise2d(xa, ya) * amp;
      amp /= 2;
      xa *= 2;
      ya *= 2;
   }

   return fin / div;
}
