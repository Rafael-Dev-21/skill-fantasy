#include <chrono>
#include <iostream>
#include <sstream>
#include <functional>

/*
extern "C" {
extern void *create_world(int, int);
extern void free_world(void *);
extern void *create_fungi(void *);
extern void *create_bat(void *);
extern void *create_player(void *);
extern void init_world(void*, int);
extern void world_update(void*, void*);
}*/

#include "skfantasy.hpp"

constexpr const auto SEED = 420UL;
constexpr const auto WIDTH = 420UL;
constexpr const auto HEIGHT = 420UL;

constexpr const auto UPDMIN = 1;
constexpr const auto UPDMAX = 10000;
constexpr const auto UPDMUL = 10;

auto timedcall(const std::string_view &sv, std::function<void(void)> fn) {
  auto t1 = std::chrono::high_resolution_clock::now();
  fn();
  auto t2 = std::chrono::high_resolution_clock::now();
  auto diff = t2 - t1;
  auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
  std::cout << sv << ": " << dur.count() << "ms" << std::endl;
}

auto main() -> int {
  auto w = create_world(WIDTH, HEIGHT);
  auto f = CreatureFactory(w);

  timedcall("world_init", [&w](){
      init_world(w, SEED);
  });

  auto dummy = f.makePlayer();

  for (int i = 0; i < 20; i++) {
    f.makeFungi();
    f.makeBat();
  }
  for (int i = UPDMIN; i <= UPDMAX; i *= UPDMUL) {
    std::stringstream ss;
    ss << "world_update*" << i;
    timedcall(ss.str(), [&w,&i,&dummy]() {
        for (int j = 0; j < i; j++) {
          world_update(w, dummy);
        }
    });
  }

  free_world(w);
}
