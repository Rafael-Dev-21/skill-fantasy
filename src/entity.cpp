#include "entity.hpp"

#include <curses.h>

Entity::Entity(IPoint pos, int sprite, int colors) :
	position(pos),
	sprite(sprite),
	colors(colors)
{}

void Entity::setPosition(IPoint npos)
{
	position = npos;
}
void Entity::move(IVector dir)
{
	position += dir;
}
void Entity::render(IVector cameraOrigin)
{
	IPoint p = position + (-cameraOrigin);
	if (p.x > 0 && p.y > 0 && COLS > p.x && LINES > p.x)
		mvaddch(p.y, p.x, sprite | COLOR_PAIR(colors));
}

IPoint Entity::getPosition()
{
	return position;
}
