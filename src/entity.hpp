#pragma once

#include <vector>

#define ENTITY_COUNT 256

enum Component {
    COMPONENT_NONE = 0,
    COMPONENT_POS = 1 << 0,
    COMPONENT_HEALTH = 1 << 1,
    COMPONENT_DRAW = 1 << 2
};

struct Position {
    int x;
    int y;
};

struct Health {
    int health;
};

struct Draw {
    char ch;
    int color;
};

class World {
public:
    World();

    std::size_t newEntity();
    void destroyEntity(std::size_t entity);

    std::vector<int> masks;
    std::vector<Position> positions;
    std::vector<Health> healths;
    std::vector<Draw> draws;
};
