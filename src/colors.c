#include <ncurses.h>
#include "colors.h"

void initPairs() {
    init_pair(GRASS_PAIR, COLOR_YELLOW, COLOR_GREEN);
    init_pair(FARM_PAIR, COLOR_YELLOW, COLOR_RED);
}
