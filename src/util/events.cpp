#include <algorithm>

#include "util/events.hpp"

EventListener::EventListener() {}

EventSystem::EventSystem() {}

void EventSystem::post(Event ev) {
  for (auto lis: listeners) {
    lis->notify(ev);
  }
}
void EventSystem::add(EventListener *lis) {
  listeners.push_back(lis);
}
void EventSystem::remove(EventListener *lis) {
  listeners.remove(lis);
}