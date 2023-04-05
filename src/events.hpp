#pragma once

#include <list>

enum EventType {
	EV_START,
	EV_QUIT,
	EV_TICK,
	EV_KEY
};

class Event {
public:
	virtual ~Event() = default;
	virtual EventType type() = 0;
};

class StartEvent: public Event {
public:
	StartEvent() {}
	EventType type() override;
};

class QuitEvent: public Event {
public:
	QuitEvent() {}
	EventType type() override;
};

class TickEvent: public Event {
public:
	TickEvent() {}
	EventType type() override;
};

class KeyEvent: public Event {
public:
	KeyEvent(int key);

	int key();

	EventType type() override;

private:
	int m_key;
};

class EventListener {
public:
	EventListener();
	virtual ~EventListener() = default;

	virtual void notify(Event *event) = 0;
};

class EventSystem {
public:
	EventSystem();

	void post(Event *e);
	void registerListener(EventListener *listener);
	void unregisterListener(EventListener *listener);

private:

	std::list<EventListener *> listeners;
};
