#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <optional>
#include "handlevector.hh"

template<typename ...Args>
class Signal {
public:
  struct Conn;
  using Callback = std::function<void(Args...)>;
  using ConnVector = HandleVector<Conn, Handle>;
  struct Conn {
    Handle handle;
    std::optional<Callback> callback;
  };

  Handle connect(Callback fn) {
    Conn conn{{}, fn};
    return listeners_.add(conn);
  }
  void emit(Args... args) {
    for (const auto& ln : listeners_)
      if (listeners_.has(ln.handle) && ln.callback)
        (*ln.callback)(args...);
  }

  void disconnect(Handle sh) {
    if (listeners_.has(sh))
      listeners_.remove(sh);
  }

private:
  ConnVector listeners_;
};
