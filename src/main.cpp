#include "events.hpp"
#include "model/game.hpp"
#include "controller/ncurses.hpp"
#include "view/ncurses.hpp"

int main(void)
{
	EventSystem system;
	Game game(system);
	NCursesController controller(system, game);
	NCursesView view(system, game);

	game.run();
	
	return 0;
}	
