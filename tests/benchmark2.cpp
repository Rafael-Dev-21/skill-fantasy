#include <chrono>
#include <iostream>
#include <sstream>
#include <functional>

extern "C" {
extern void *create_world(int, int);
extern void *create_fungi(void *);
extern void *create_bat(void *);
extern void *create_player(void *);
extern void init_world(void*, int);
extern void world_update(void*, void*);
extern void free_world(void*);
}

constexpr const auto SEED = 420UL;
constexpr const auto WIDTH = 420UL;
constexpr const auto HEIGHT = 420UL;

auto timedcall(const std::string_view &sv, std::function<void(void)> fn) {
  auto t1 = std::chrono::high_resolution_clock::now();
  fn();
  auto t2 = std::chrono::high_resolution_clock::now();
  auto diff = t2 - t1;
  auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
  std::cout << sv << ": " << dur.count() << "ms" << std::endl;
}

auto averagecalls(const std::string_view &sv, int turns, std::function<void(void)> fn) {
  auto sum = 0;
  for (int k = 0; k < turns; k++) {

    auto t1 = std::chrono::high_resolution_clock::now();
  fn();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = t2 - t1;
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    sum += dur.count();
  }
  std::cout << sv << "(" << turns << "): " << (static_cast<float>(sum) / turns) << "ms avg." << std::endl;
}

auto main() -> int {
  averagecalls("full process", 100, [](){
    auto w = create_world(WIDTH, HEIGHT);
    init_world(w, SEED);
    auto dummy = create_player(w);
    for (int i = 0; i < 10; i++) {
      create_fungi(w);
      create_bat(w);
    }
    world_update(w, dummy);
    free_world(w);
  });

  auto sum = 0;
  for (int k = 0; k < 100; k++) {
    auto w = create_world(WIDTH, HEIGHT);
    init_world(w, SEED);
    auto dummy = create_player(w);
    for (int i = 0; i < 10; i++) {
      create_fungi(w);
      create_bat(w);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    world_update(w, dummy);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = t2 - t1;
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    sum += dur.count();
  }
  std::cout << "Only update" << "(" << 100 << "): " << (static_cast<float>(sum) / 100.0f) << "ms avg." << std::endl;
}
