#include "skfantasy.h"

void move_from(Point *pos, Direction dir)
{	
	if (dir == LEFT) pos->x -= 1;
	if (dir == DOWN) pos->y += 1;
	if (dir == UP) pos->y -= 1;
	if (dir == RIGHT) pos->x += 1;
}

Direction dir_from_ch(int ch, Direction fall)
{
	if (ch == 'h') return LEFT;
	if (ch == 'j') return DOWN;
	if (ch == 'k') return UP;
	if (ch == 'l') return RIGHT;
	return fall;
}

Point point_from_dir(Direction dir)
{
	Point result = {0, 0};

	switch (dir) {
	case UP:
		result.y = -1;
		break;
	case DOWN:
		result.y = 1;
		break;
	case LEFT:
		result.x = -1;
		break;
	case RIGHT:
		result.x = 1;
		break;
	default:
		result.x = 0;
		result.y = 0;
	}
	
	return result;
}
