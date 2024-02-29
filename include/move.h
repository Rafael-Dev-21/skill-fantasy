#ifndef MOVE_H
#define MOVE_H

#include "position.h"
#include "world.h"

// move
void move_from(Point *, Direction);
void move_and_collide(Map * const, Point *, Direction);
Direction dir_from_ch(int, Direction);

#endif
