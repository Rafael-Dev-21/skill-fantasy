#pragma once

#include <memory>

#include "entity.hpp"
#include "level.hpp"

enum EngineState { ENGINE_TITLE, ENGINE_GEN, ENGINE_PLAY, ENGINE_EXIT };

typedef EngineState (*EngineAction)();

EngineState titleAction();
EngineState genAction();
EngineState playAction();

class Engine {
 public:
  static EngineAction actionTable[];

  Engine(bool blackBG = false);
  ~Engine();

  void run();

 private:
  void colors();

  EngineState state;
  bool blackBG;
};

extern Level *level;
extern Entity *player;
