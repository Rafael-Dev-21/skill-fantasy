#include "curses_window.hh"
#include "signal.hh"
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <map>

struct KeyCommand {
  std::string playerId;
  int keyPressed;
};

struct Game {
  using mapent = std::map<std::string, Pt>;
  mapent players, fruits;

  std::string msg;

  Game() {
    players["player1"] = { 1, 1 };
    players["player2"] = { 9, 9 };
    fruits["fruit1"] = { 3, 1 };
  }

  void movePlayer(KeyCommand cmd) {
    std::ostringstream oss;
    oss << "Moving " << cmd.playerId << " with " << (char)cmd.keyPressed;
    msg = oss.str();

    auto keyPressed = cmd.keyPressed;
    auto& player = players[cmd.playerId];

    switch (keyPressed) {
    case 'j':
      if (player.y+1 < 10) player.y++;
      break;
    case 'l':
      if (player.x+1 < 10) player.x++;
      break;
    case 'k':
      if (player.y-1 >= 0) player.y--;
      break;
    case 'h':
      if (player.x-1 >= 0) player.x--;
      break;
    }
  }
};

class KeyboardListener {
public:
  KeyboardListener(Game& game) :
    game_(game) {}

  void handleKey(int c) {
    if (c == ERR)
      return;
    KeyCommand cmd{
      "player1",
      c
    };
    notify_all(cmd);
  }

  Handle subscribe(std::function<void(KeyCommand)> listener) {
    return on_key_.connect(listener);
  }

  void unsubscribe(Handle ht) {
    on_key_.disconnect(ht);
  }

private:
  void notify_all(KeyCommand cmd) {
    on_key_.emit(cmd);
  }

  Game& game_;
  Signal<KeyCommand> on_key_;
};

auto main() -> int
{
  using namespace std::chrono_literals;
  CursesWindow root;
  int bgPair = 1, playerPair = 2, fruitPair = 3;
  if (has_colors()) {
    start_color();
    init_pair(bgPair, COLOR_WHITE, COLOR_WHITE);
    init_pair(playerPair, COLOR_BLACK, COLOR_WHITE);
    init_pair(fruitPair, COLOR_GREEN, COLOR_WHITE);
  }

  Game game;
  KeyboardListener keyboardListener(game);
  keyboardListener.subscribe([&game](KeyCommand cmd) {
    game.movePlayer(cmd);
  });

  do {
    CursesWindow screen = root.make_child(1, 1, 22, 12);
    screen.set_nodelay(true);
    for (;;) {
      screen.reset();
      screen.box(0, 0);
      for (int y=0; y<10; y++) {
        for (int x=0; x<20; x++) {
          int attr = COLOR_PAIR(bgPair);
          CursesAttrGuard guard(screen, attr);
          screen.move_cursor(x+1, y+1);
          screen.putch(' ');
        }
      }

      for (auto& p : game.players) {
        Pt& pt = p.second;
        CursesAttrGuard guard(screen, COLOR_PAIR(playerPair));
        screen.move_cursor(pt.x*2+1, pt.y+1);
        screen.putch('@');
      }
      for (auto& f : game.fruits) {
        Pt& pt = f.second;
        CursesAttrGuard guard(screen, COLOR_PAIR(fruitPair));
        screen.move_cursor(pt.x*2+1, pt.y+1);
        screen.putch('*');
      }

      root.move_cursor(2, 14);
      root.putstr("%s", game.msg.c_str());

      root.flush();

      std::this_thread::sleep_for(15ms);

      int c = screen.readch();
      if (c == 27 || c == 10) { break; }

      keyboardListener.handleKey(c);
    }
  } while (0);
}
