#pragma once
#include <entt/entt.hpp>
#include "world.hpp"

entt::entity make_player(World& world);
entt::entity make_bat(World& world);
entt::entity make_fungi(World& world);
entt::entity make_fire(World& world, Point cell);
