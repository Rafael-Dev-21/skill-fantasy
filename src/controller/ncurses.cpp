#include "ncurses.hpp"
#include "../common.hpp"

NCursesController::NCursesController(EventSystem &evSystem, Game game) :
	evSystem(evSystem),
	game(game)
{
	evSystem.registerListener(this);
}

void NCursesController::notify(Event *event)
{
	if (event->type() == EV_TICK) {
		int input = getch();

		switch(input) {
		case 'q':
			evSystem.post(new QuitEvent());
			break;
		default:
			evSystem.post(new KeyEvent(input));
		}
	}
}
