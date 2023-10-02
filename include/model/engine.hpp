#pragma once

#include <string>

#include "entity.hpp"
#include "level.hpp"

#include "util/events.hpp"

class Engine: public EventListener {
 public:
  Engine(EventSystem &evSystem);

  void run();
  
  void notify(Event ev) override;
  State getState();
  std::string getVersion();
  World * getWorld();
  Entity * getPlayer();

 private:
 void movePlayer(int x, int y);
 
 EventSystem &evSystem;
 State state;
 
 bool running = false;
 std::string version;
 
 World * world = nullptr;
 Entity * player = nullptr;
};
