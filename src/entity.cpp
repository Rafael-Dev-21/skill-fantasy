#include "common.hpp"
#include "entity.hpp"

World::World() :
    masks(ENTITY_COUNT),
    positions(ENTITY_COUNT),
    healths(ENTITY_COUNT),
    draws(ENTITY_COUNT)
{}

std::size_t World::newEntity()
{
    std::size_t entity;
    for (entity = 0; entity < ENTITY_COUNT; ++entity) {
        if (masks[entity] == COMPONENT_NONE) {
            return entity;
        }
    }

    return (ENTITY_COUNT);
}

void World::destroyEntity(std::size_t entity)
{
    masks[entity] = COMPONENT_NONE;
}
