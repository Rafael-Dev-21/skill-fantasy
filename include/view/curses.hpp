#pragma once

#include "model/engine.hpp"
#include "util/events.hpp"
#include "util/geom.hpp"

struct CursesCamera {
  public:
  IPoint center();
  IVector origin();
  
  int width;
  int height;
  IPoint pos;
};

class CursesView: public EventListener {
  public:
  CursesView(Engine& engine, EventSystem& evSystem);
  ~CursesView();
  
  void notify(Event ev);
  
  private:
  void drawTitle();
  void drawGen();
  void drawPlay();
  
  void drawPlayer();
  void drawWorld();
  
  void colors();
  
  Engine& engine;
  EventSystem& evSystem;
  
  CursesCamera cam;
};