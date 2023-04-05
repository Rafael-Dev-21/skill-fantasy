#include "game.hpp"

Game::Game(EventSystem &evSystem) :
	evSystem(evSystem),
	level(new Level())
{
	evSystem.registerListener(this);
}

void Game::run()
{
	running = true;
	evSystem.post(new StartEvent());
	while (running)
	{
		evSystem.post(new TickEvent());
	}
}

void Game::notify(Event *event)
{
	if (event->type() == EV_START) {
        	noise.m_octaves = 3;

		level->genOverworld(noise);
	}
	if (event->type() == EV_QUIT) {
		running = false;
	}
}

Level * Game::getLevel()
{
	return level;
}
