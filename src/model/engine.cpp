#include <chrono>
#ifdef __MINGW32__
#include "mingw.thread.h"
#else
#include <thread>
#endif

#include <cstdlib>
#include <ctime>

#include "model/engine.hpp"

Engine::Engine(EventSystem &evSystem) :
  evSystem(evSystem)
{
  state = ST_TITLE;
  
  evSystem.add(this);
}

void Engine::run() {
  running = true;
  
  while (running) {
    Event ev;
    ev.type = EV_TICK;
    
    evSystem.post(ev);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
}

void Engine::notify(Event ev) {
  switch(ev.type) {
    case EV_STATE:
    state = ev.as.change.state;
    
    if (state == ST_GEN) {
      std::thread load([this]() {
        srand(time(nullptr));
        world = new World();
        player = new Entity(world->getSpawn());
        
        Event ev;
        ev.type = EV_STATE;
        ev.as.change.state = ST_PLAY;
        
        evSystem.post(ev);
      });
      
      load.join();
    }
    
    if (state == ST_TITLE) {
      delete player; player = nullptr;
      delete world; world = nullptr;
    }
    
    break;
    case EV_MOVE: {
      switch(ev.as.move.dir) {
        case D_WEST: movePlayer(-1, 0); break;
        case D_SOUTH: movePlayer(0, 1); break;
        case D_NORTH: movePlayer(0, -1); break;
        case D_EAST: movePlayer(1, 0); break;
      }
    }
    break;
    case EV_QUIT:
    running = false;
    break;
    default:
    break;
  }
}

State Engine::getState() {
  return state;
}

World * Engine::getWorld() {
  return world;
}

Entity * Engine::getPlayer() {
  return player;
}

void Engine::movePlayer(int x, int y) {
  if (!player || !world) return;
  
  IVector dir(x, y);
  IPoint future = player->getPosition() + dir;
  
  if (!world->inBounds(future.x, future.y)) return;
  
  auto obj = world->tileAt(future.x, future.y).fixedObject;
  
  if (obj && obj->block) return;
  
  player->move(dir);
  world->checkChunks(player->getPosition());
}