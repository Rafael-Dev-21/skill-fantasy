#pragma once

#include "level.hpp"
#include "../noise.hpp"
#include "../point.hpp"
#include "../events.hpp"

class Game: public EventListener {
public:
	Game(EventSystem &evSystem);
	~Game() = default;

	void run();

	void notify(Event *event) override;

	Level *getLevel();
private:

	EventSystem &evSystem;
	Level *level;
	Noise noise;

	bool running;
	bool paused;
};
