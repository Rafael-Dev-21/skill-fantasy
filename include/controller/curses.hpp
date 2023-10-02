#pragma once

#include "model/engine.hpp"
#include "util/events.hpp"

class CursesController: public EventListener {
  public:
  CursesController(Engine &engine, EventSystem &evSystem);
  
  void notify(Event ev);
  
  private:
  void titleInput();
  void playInput();
  
  Engine& engine;
  EventSystem &evSystem;
};