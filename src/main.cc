#include "ui.hh"
#include "handlevector.hh"
#include "geom.hh"
#include "game.hh"
#include <thread>
#include <chrono>

int main()
{
  using namespace std::chrono_literals;
  CursesWindow root;
  constexpr int stat_height = 5;
  constexpr int stat_width = 15;
  CursesWindow stat_area(0, 0, stat_width*2, stat_height);
  constexpr int play_width = 30;
  constexpr int play_height = 30;
  CursesWindow play_area(0, stat_height, play_width*2, play_height);
  play_area.set_nodelay(true);

  Game game;
  int input;
  auto player = game.addPlayer(10, 10);
  game.populateTrees(play_width, play_height);
  game.drawStats(stat_area, player);
  game.drawAll(play_area);
  root.flush();

  while ((input = play_area.readch()) != 'q') {
    game.drawStats(stat_area, player);
    Pt dir{0, 0};
    switch (input) {
    case 'h':
      dir.x = -1;
      break;
    case 'j':
      dir.y = 1;
      break;
    case 'k':
      dir.y = -1;
      break;
    case 'l':
      dir.x = 1;
      break;
    }
    if (game.mode == Game::Mode::Normal) {
      game.get(player).move(game, dir.x, dir.y, play_width, play_height);
      if (input == 'v') {
        game.placeCursor(game.get(player).x, game.get(player).y);
        game.mode = Game::Mode::Visual;
      }
    }
    else if (game.mode == Game::Mode::Visual) {
      game.placeCursor(game.get(game.cursor).x + dir.x, game.get(game.cursor).y + dir.y);
      if (input == 'm')
        game.placeMark(game.get(game.cursor).x, game.get(game.cursor).y);
      else if (input == 'M')
        game.clearMark();
      else if (input == 'b' || input == 'p') {
        game.mapFnOverArea([&game, &player, input](ObjectHandle handle, int x, int y) {
          game.get(player).kill(game, handle);
          if (input == 'p' && game.get(player).wood > 5) {
            if (game.placeWall(x, y))
              game.get(player).wood -= 5;
          }
        });
      }
      else if (input == 27) {
        game.clearCursorAndMark();
        game.mode = Game::Mode::Normal;
      }
    }

    game.drawAll(play_area);
    root.flush();
    std::this_thread::sleep_for(15ms);
  }
}
