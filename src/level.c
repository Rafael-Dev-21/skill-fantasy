#include <ncurses.h>
#include "level.h"
#include "colors.h"

void genOverworld(Level *level)
{
    for (int row = 0; row < MAP_SIZE; row++) {
        for (int col = 0; col < MAP_SIZE; col++) {
            Tile *tile = &level->tiles[row][col];

            tile->ch = ',';
            tile->color = GRASS_PAIR;
            tile->solid = false;
            tile->visible = true;
        }
    }
}

void genCave(Level *level)
{

}

void renderLevel(Level *level, Rect viewport)
{
    for (int row = viewport.top; row < viewport.bottom; row++) {
        for (int col = viewport.left; col < viewport.right; col++) {
            if (!inBounds(row, col)) continue;

            int y = row - viewport.top;
            int x = col - viewport.left;

            Tile *tile = &level->tiles[row][col];

            if (!tile->visible) continue;

            mvaddch(y, x, tile->ch | COLOR_PAIR(tile->color));
        }
    }
}

Tile getTile(Level *level, int row, int col)
{
    return level->tiles[row][col];
}

void setTile(Level *level, int row, int col, Tile *tile)
{
    level->tiles[row][col].ch = tile->ch;
    level->tiles[row][col].color = tile->color;
    level->tiles[row][col].visible = tile->visible;
    level->tiles[row][col].solid = tile->solid;
}

bool inBounds(int row, int col)
{
    return (row >= 0 && row < MAP_SIZE && col >= 0 && col < MAP_SIZE);
}
