#include <curses.h>

#include "view/curses.hpp"

IPoint CursesCamera::center() {
  return IPoint(width / 2, height / 2);
}
IVector CursesCamera::origin() {
  return pos - center();
}

CursesView::CursesView(Engine& engine, EventSystem& evSystem):
  engine(engine),
  evSystem(evSystem)
{
  evSystem.add(this);
  initscr();
  noecho();
  curs_set(0);
  timeout(0);

  colors();
}
CursesView::~CursesView() {
  evSystem.remove(this);
  endwin();
}

void CursesView::notify(Event ev) {
  if (ev.type == EV_TICK) {
    getmaxyx(stdscr, cam.height, cam.width);

    switch (engine.getState()) {
      case ST_TITLE: drawTitle(); break;
      case ST_GEN: drawGen(); break;
      case ST_PLAY: drawPlay(); break;
    }
  }
}

void CursesView::drawTitle() {
  int startx = cam.center().x - 8;

  clear();
  mvaddstr(2, startx, "#== # # =#= #   #  ");
  mvaddstr(3, startx, "#=# ##   #  #   #  ");
  mvaddstr(4, startx, "==# # # =#= #== #==");
  mvaddstr(5, startx, "@====>FANTASY<====@");
  mvaddstr(6, startx, "v0.1.0");

  mvaddstr(8, startx, "s to start, ESC to quit");
  refresh();
}
void CursesView::drawGen() {
  mvaddstr(5, cam.center().x - 8, "Creating world...");
  refresh();
}
void CursesView::drawPlay() {
  if (!engine.getPlayer() || !engine.getWorld()) return;
  
  auto player = engine.getPlayer();
  auto world = engine.getWorld();
  
  if (player->getPosition().x > cam.center().x &&
      world->getWidth() - cam.center().x > player->getPosition().x) {
    cam.pos.x = player->getPosition().x;
  }
  
    if (player->getPosition().y > cam.center().y &&
      world->getHeight() - cam.center().y > player->getPosition().y) {
    cam.pos.y = player->getPosition().y;
  }

  drawWorld();
  drawPlayer();

  refresh();
}

void CursesView::drawPlayer() {
  auto pos = engine.getPlayer()->getPosition() + (-cam.origin());
  
  mvaddch(pos.y, pos.x, '@' | COLOR_PAIR(5));
}

void CursesView::drawWorld() {
  for (int y = 0; y < cam.height; y++) {
    for (int x = 0; x < cam.width; x++) {
      int mapx = x + cam.origin().x;
      int mapy = y + cam.origin().y;

      auto tile = engine.getWorld()->tileAt(mapx, mapy);

      int graphic = ' ';
      if (tile.fixedObject) {
        graphic = tile.fixedObject->sprite | COLOR_PAIR(tile.fixedObject->colors);
      } else {
        graphic = tile.sprite | COLOR_PAIR(tile.colors);
      }
      mvaddch(y, x, graphic);
    }
  }
}

void CursesView::colors() {
  if (has_colors()) {
    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_YELLOW, 230);
    init_pair(3, COLOR_CYAN, 12);
    init_pair(4, COLOR_BLACK, 8);
    init_pair(5, COLOR_RED, COLOR_MAGENTA);
    init_pair(6, COLOR_YELLOW, 22);
    init_pair(7, COLOR_YELLOW, 73);
  }
}