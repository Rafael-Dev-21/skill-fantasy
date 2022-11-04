#include "common.h"
#include "draw.h"
#include <iostream>

void draw::setup() {
  std::cout << "draw setup\n";
  initscr();
  noecho();
  curs_set(0);
}

static void draw_tile(int t, int y, int x)
{
    int result = ' ';

    switch (t) {
        case TILE_GRASS:
            result = ',' | COLOR_PAIR(SKPAIR_GRASS);
            break;
        case TILE_SAND:
            result = '~' | COLOR_PAIR(SKPAIR_SAND);
            break;
        case TILE_WATER:
            result = '~' | COLOR_PAIR(SKPAIR_WATER);
            break;
        case TILE_MOUNTAIN:
            result = '^' | COLOR_PAIR(SKPAIR_MOUNTAIN);
            break;
        default:
            break;
    }

    mvaddch(y, x, result);
}

void draw::draw_map(Game *g)
{
    clear();
    auto view_radius = 100;
    int center_row = LINES / 2;
    int center_col = COLS / 2;

    auto &layer = g->layers.at(g->currentLayer);

    for (int row = -view_radius; row <= view_radius; row++) {
        for (int col = -view_radius; col <= view_radius; col++) {
            int py = g->player.pos.y + row;
            int px = g->player.pos.x + col;

            if (layer.inBounds(py, px)) {
                int t = layer.tileAt(py, px);
                int rely = center_row + row;
                int relx = center_col + col;

                draw_tile(t, rely, relx);
            }
        }
    }

    mvaddch(center_row, center_col, '@' | COLOR_PAIR(SKPAIR_PLAYER));
    refresh();
}

void draw::close() { endwin(); }
