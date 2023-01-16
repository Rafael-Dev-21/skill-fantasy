#pragma once

#include "entity.hpp"
#include "level.hpp"

struct Game {
public:
    Game();

    bool init();
    void loop();
    void close();

    Level level;
    World world;

    Rect viewport;

private:
    void processInput();
    void update();
    void render();

    int currentInput = ' ';
};

