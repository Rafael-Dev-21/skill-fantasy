#include "move.h"

void move_from(Point *pos, Direction dir)
{	
	if (dir == LEFT) pos->x -= 1;
	if (dir == DOWN) pos->y += 1;
	if (dir == UP) pos->y -= 1;
	if (dir == RIGHT) pos->x += 1;
}

void move_and_collide(Map * const map, Point *pos, Direction dir)
{
	Point next = *pos;
	move_from(&next, dir);
	if (!is_solid(map, next)) move_from(pos, dir);
}

Direction dir_from_ch(int ch, Direction fall)
{
	if (ch == 'h') return LEFT;
	if (ch == 'j') return DOWN;
	if (ch == 'k') return UP;
	if (ch == 'l') return RIGHT;
	return fall;
}
