#include <string>



enum GameStateEnum {
	STATE_START,
	STATE_BATTLE,
	STATE_END
};

class GameState final {
public:
	GameState();
	GameState(GameStateEnum state);

	void run();

	void changeState(GameStateEnum new_state);
private:

	GameStateEnum game_state;
};
