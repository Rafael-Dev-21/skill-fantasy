#include "game.h"

#include "../view/draw.h"
#include "../view/view.h"

Game::Game() {
  currentLayer = 0;
  Position startPos = layers.at(currentLayer).generate();

  player.move(startPos);
  currentInput = -1;
}

Game::~Game() = default;

void Game::update() {
  Position next(player.pos.y, player.pos.x);

  switch (currentInput) {
    case 'k':
      next.y -= 1;
      break;
    case 'j':
      next.y += 1;
      break;
    case 'h':
      next.x -= 1;
      break;
    case 'l':
      next.x += 1;
      break;
    default:
      break;
  }

  if (layers.at(currentLayer).walkable(next.y, next.x)) player.move(next);
}

void Game::nextInput() { currentInput = getch(); }

void Game::gameLoop() {
  while (currentInput != 'q') {
    update();
    view::draw::draw_map(this);
    nextInput();
  }
}

void Game::close() { view::draw::close(); }
