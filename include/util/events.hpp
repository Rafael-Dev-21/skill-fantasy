#pragma once

#include <list>

enum EventType {
  EV_TICK,
  EV_MOVE,
  EV_STATE,
  EV_QUIT,
};

enum State { 
  ST_TITLE,
  ST_GEN,
  ST_PLAY,
};

enum Direction {
  D_NORTH,
  D_WEST,
  D_EAST,
  D_SOUTH
};

struct Event {
  EventType type;
  
  union {
    struct {
      Direction dir;
    } move;
    struct {
      State state;
    } change;
  } as;
};

class EventListener {
  public:
  EventListener();
  virtual ~EventListener() = default;
  virtual void notify(Event ev) = 0;
};

class EventSystem {
  public:
  EventSystem();
  
  void post(Event ev);
  void add(EventListener *lis);
  void remove(EventListener *lis);
  
  private:
  std::list<EventListener *> listeners;
};