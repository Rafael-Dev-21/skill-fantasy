#ifndef _GAME_H_
#define _GAME_H_

#include <stack>
#include "stackfsm.hh"

class Game {
public:
	void run();
	void run_set(bool flag);
	static Game *getInstance();
	Game(Game&)=delete;
	void operator=(const Game&)=delete;

private:
	StackFSM machine;
	bool running;
	static Game *instance;

	Game();
	~Game();
};

#endif
