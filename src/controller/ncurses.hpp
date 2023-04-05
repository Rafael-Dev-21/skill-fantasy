#pragma once

#include "../events.hpp"
#include "../model/game.hpp"

class NCursesController: public EventListener {
public:
	NCursesController(EventSystem &evSystem, Game game);

	void notify(Event *event);

private:

	EventSystem &evSystem;
	Game game;
};
