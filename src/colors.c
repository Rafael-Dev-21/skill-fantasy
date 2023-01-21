#include "skfantasy.h"

bool colors_init(void)
{
	if (!has_colors()) return false;
	start_color();

	init_pair(PAIR_GRASS, COLOR_GREEN, COLOR_BLACK);
	init_pair(PAIR_MUD, COLOR_RED, COLOR_BLACK);

	return true;
}
