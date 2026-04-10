#ifndef COLORS_H
#define COLORS_H

#include "common.h"

enum game_colors {
	SKPAIR_GRASS = 1,
	SKPAIR_SAND,
	SKPAIR_WATER,
	SKPAIR_MOUNTAIN,
	SKPAIR_PLAYER,
	SKPAIR_COUNT
};

bool setup_colors(void);

#endif
