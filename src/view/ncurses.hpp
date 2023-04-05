#pragma once

#include "../events.hpp"
#include "../model/game.hpp"
#include "../point.hpp"

class NCursesView: public EventListener {
public:
	NCursesView(EventSystem &evSystem, Game game);

	void notify(Event *event);

	void init();

private:

	void renderLevel();
	void renderTile(int y, int x, Tile tile);

	EventSystem &evSystem;
	Game game;
	bool isInitialized;

	Point2D cameraPos{10, 10};
	int cameraWidth = 40;
	int cameraHeight = 20;
};
