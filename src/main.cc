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
  Pt root_dims = root.dims();
  Pt stat_pos{};
  Pt stat_dims{root_dims.x, 5};
  CursesWindow stat_area(stat_pos, stat_dims);
  Pt play_pos{0, stat_dims.y};
  Pt play_dims{root_dims.x, root_dims.y-stat_dims.y};
  CursesWindow play_area(play_pos, play_dims);
  play_area.set_nodelay(true);

  Pt game_dims = play_dims;
  game_dims.x /= 2;
  Game game{game_dims};
  int input;
  auto player = game.addPlayer(10, 10);
  game.populateTrees(game_dims.x, game_dims.y);
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
      game.get(player).move(game, dir.x, dir.y, game_dims.x, game_dims.y);
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
