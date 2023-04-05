#include "events.hpp"
#include <algorithm>

EventType StartEvent::type()
{
	return EV_START;
}

EventType QuitEvent::type()
{
        return EV_QUIT;
}

EventType TickEvent::type()
{
        return EV_TICK;
}

KeyEvent::KeyEvent(int key) :
	m_key(key)
{}

int KeyEvent::key()
{
	return m_key;
}

EventType KeyEvent::type()
{
        return EV_KEY;
}

EventListener::EventListener()
{}

EventSystem::EventSystem()
{}

void EventSystem::post(Event *event)
{
	for (auto listener : listeners) {
		listener->notify(event);
	}

	delete event;
}

void EventSystem::registerListener(EventListener *listener)
{
	listeners.push_back(listener);
}

void EventSystem::unregisterListener(EventListener *listener)
{
	listeners.remove(listener);
}
