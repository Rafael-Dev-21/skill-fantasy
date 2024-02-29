#ifndef POSITION_H
#define POSITION_H

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
} Direction;

typedef struct {
	int x;
	int y;
} Point;

#endif
