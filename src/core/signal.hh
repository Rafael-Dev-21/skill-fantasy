#pragma once

#include <vector>
#include <algorithm>
#include <functional>

template<typename ...Args>
class Signal {
public:
  using Callback = std::function<void(Args...)>;

  Callback connect(Callback fn) {
    listeners_.push_back(fn);
    return fn;
  }
  void emit(Args... args) {
    for (const auto& ln : listeners_)
      if (ln) ln(args...);
  }

  void disconnect(Callback fn) {
    listeners_.erase(std::remove(listeners_.begin(), listeners_.end(), fn), listeners_.end());
  }

private:
  std::vector<Callback> listeners_;
};
