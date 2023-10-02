#include <curses.h>

#include "controller/curses.hpp"

CursesController::CursesController(Engine &engine, EventSystem &evSystem):
  engine(engine),
  evSystem(evSystem)
{
  evSystem.add(this);
}

void CursesController::notify(Event ev) {
  if (ev.type == EV_TICK) {
    switch(engine.getState()) {
      case ST_TITLE:
      titleInput();
      break;
      case ST_PLAY:
      playInput();
      break;
      default:
      break;
    }
  }
}

void CursesController::titleInput() {
  switch (getch()) {
    case 27: {
      Event ev;
      ev.type = EV_QUIT;
      
      evSystem.post(ev);
    }
    break;
    case 's': {
      Event ev;
      ev.type = EV_STATE;
      
      ev.as.change.state = ST_GEN;
      
      evSystem.post(ev);
    }
  }
}

void CursesController::playInput() {
  switch (getch()) {
    case 27: {
      Event ev;
      ev.type = EV_STATE;
      ev.as.change.state = ST_TITLE;
      
      evSystem.post(ev);
    }
    break;
    case 'h': {
      Event ev;
      ev.type = EV_MOVE;
      ev.as.move.dir = D_WEST;
      
      evSystem.post(ev);
    }
    break;
    case 'j': {
      Event ev;
      ev.type = EV_MOVE;
      ev.as.move.dir = D_SOUTH;
      
      evSystem.post(ev);
    }
    break;
    case 'k': {
      Event ev;
      ev.type = EV_MOVE;
      ev.as.move.dir = D_NORTH;
      
      evSystem.post(ev);
    }
    break;
    case 'l': {
      Event ev;
      ev.type = EV_MOVE;
      ev.as.move.dir = D_EAST;
      
      evSystem.post(ev);
    }
    break;
  }
}