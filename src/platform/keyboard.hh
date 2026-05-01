#include "ui.hh"
#include "signal.hh"

struct KeyboardListener {
public:
  Signal<int> onReadch;
  Window& window_;

  KeyboardListener(Window& window) :
    window_(window) {}

  void poll() {
    int ch = window_.readch();
    if (ch != ERR)
      onReadch.emit(ch);
  }
};
