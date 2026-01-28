#pragma once

#include <vector>
#include <algorithm>
#include <functional>

template<typename ...Args>
class Signal {
public:
  using Callback = std::function<void(Args...)>;

  void connect(Callback fn) {
    listeners_.push_back(fn);
  }
  void emit(Args... args) {
    for (const auto& ln : listeners_)
      if (ln) ln(args...);
  }

private:
  std::vector<Callback> listeners_;
};
