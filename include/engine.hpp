#pragma once

#include <memory>

#include "level.hpp"
#include "entity.hpp"

enum EngineState {
	ENGINE_TITLE,
	ENGINE_GEN,
	ENGINE_PLAY,
	ENGINE_EXIT
};

typedef EngineState (*EngineAction)();

EngineState titleAction();
EngineState genAction();
EngineState playAction();

class Engine {
public:
	static EngineAction actionTable[];

	Engine();
	~Engine();

	void run();

private:
	void colors();

	EngineState state;
};

extern Level *level;
extern Entity *player;
