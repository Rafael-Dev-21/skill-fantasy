#include "ncurses.hpp"
#include "../common.hpp"

NCursesView::NCursesView(EventSystem &evSystem, Game game) :
	evSystem(evSystem),
	game(game)
{
	evSystem.registerListener(this);
}

void NCursesView::notify(Event *event)
{
	if (event->type() == EV_START) {
		init();
	} else if (event->type() == EV_QUIT) {
		isInitialized = false;
		endwin();
	} else if (event->type() == EV_TICK) {
		if (!isInitialized) return;

		renderLevel();
	} else if (event->type() == EV_KEY) {
		if (!isInitialized) return;

		KeyEvent *kevent = static_cast<KeyEvent *>(event);

		switch(kevent->key()) {
		case 'h': cameraPos.move(0, -1); break;
		case 'j': cameraPos.move(1, 0); break;
		case 'k': cameraPos.move(-1, 0); break;
		case 'l': cameraPos.move(0, 1); break;
		}
	}
}

void NCursesView::init()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	timeout(100);
	isInitialized = true;
}

void NCursesView::renderLevel()
{
	Level *level = game.getLevel();

	for (int j = cameraPos.y(); j < cameraPos.y() + cameraHeight; j++) {
		for (int i = cameraPos.x(); i < cameraPos.x() + cameraWidth; i++) {
			int y = j - cameraPos.y();
			int x = i - cameraPos.x();

			if (j < 0 || j > LEVEL_SIZE - 1 || i < 0 || i > LEVEL_SIZE - 1) {
				mvaddch(y, x, ' ');
			} else {
				renderTile(y, x, level->at(j, i));
			}
		}
	}
}

void NCursesView::renderTile(int y, int x, Tile tile)
{
	int sprite = ' ';

	switch(tile.getType()) {
	case TILE_WATER:
		sprite = '7';
		break;
	case TILE_SAND:
		sprite = '~';
		break;
	case TILE_GRASS:
		sprite = ',';
		break;
	case TILE_STONE:
		sprite = '#';
		break;
	default:
		break;
	}

	mvaddch(y, x, sprite);
}
