#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <functional>

#include <raylib.h>

struct Point {
  int x;
  int y;
};

struct State {
  std::unordered_map<std::string, Point> players;
  std::unordered_map<std::string, Point> fruits;
  int width;
  int height;
};

struct KeyCmd {
  std::string playerId;
  int keyPressed;
};

class Game {
public:
  Game() {

  }

  void movePlayer(KeyCmd cmd) {
    std::cout << "Moving " << cmd.playerId << " with (" << cmd.keyPressed << ")" << std::endl;
    auto keyPressed = cmd.keyPressed;
    auto playerId = cmd.playerId;
    auto& player = state.players[playerId];

    if (keyPressed == KEY_H && player.x > 0) {
      player.x--;
    } else if (keyPressed == KEY_L && player.x < state.width-1) {
      player.x++;
    } else if (keyPressed == KEY_K && player.y > 0) {
      player.y--;
    } else if (keyPressed == KEY_J && player.y < state.height-1) {
      player.y++;
    }
  }

  State getState() { return state; }
private:
  State state{
    { { "player1", { 12, 12 } } },
    {
      { "fruit1", { 5, 3 } },
      { "fruit2", { 19, 21 } }
    },
    25,
    25
  };
};

class KeyboardListener {
public:
  KeyboardListener() {}

  void subscribe(std::function<void(KeyCmd)> listener) {
    listeners.push_back(listener);
  }
  void notifyAll(KeyCmd cmd) {
    for (auto& l : listeners) {
      l(cmd);
    }
  }
  void checkKeys() {
    auto keyPressed = GetKeyPressed();
    KeyCmd cmd{"player1", keyPressed};
    if (keyPressed) {
      notifyAll(cmd);
    }
  }

private:
  std::vector<std::function<void(KeyCmd)>> listeners;
};

auto renderScreen(const State& s, int w, int h) -> void;

auto main() -> int
{
  Game game;
  KeyboardListener keyboardListener;
  keyboardListener.subscribe([&game](auto cmd){game.movePlayer(cmd);});
  InitWindow(800, 600, "Skill Fantasy v0.4.0 - Dandy World Upt");
  SetTargetFPS(30);
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  while (!WindowShouldClose()) {
    keyboardListener.checkKeys();
    renderScreen(game.getState(), GetScreenWidth(), GetScreenHeight());
  }
  CloseWindow();

  return 0;
}

auto renderScreen(const State& s, int w, int h) -> void
{
  Point tileSize{w/s.width, h/s.height};
  int fontSize{(int)(tileSize.y*0.9)};
  Point textOffset{(tileSize.x-fontSize)/4, (tileSize.y-fontSize)/4};

  BeginDrawing();
  ClearBackground(RAYWHITE);
  for (auto& player : s.players) {
    DrawText(
        "@",
        textOffset.x+player.second.x*tileSize.x,
        textOffset.y+player.second.y*tileSize.y,
        fontSize, BLACK);
  }
  for (auto& fruit : s.fruits) {
    DrawText(
        "*",
        textOffset.x+fruit.second.x*tileSize.x,
        textOffset.y+fruit.second.y*tileSize.y,
        fontSize, GREEN);
  }
  EndDrawing();
}
