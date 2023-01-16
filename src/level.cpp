#include "common.hpp"
#include "level.hpp"
#include "colors.hpp"

Level::Level(int w, int h) :
    width(w),
    height(h),
    tiles(w * h)
{

}

Level::~Level() {}

void Level::genOverworld()
{
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int index = row * width + col;

            tiles[index].ch = ',';
            tiles[index].color = GRASS_PAIR;
            tiles[index].solid = false;
            tiles[index].visible = true;
        }
    }
}

void Level::render(Rect viewport)
{
    for (int row = viewport.top; row < viewport.bottom; row++) {
        for (int col = viewport.left; col < viewport.right; col++) {
            if (!inBounds(row, col)) continue;

            int y = row - viewport.top;
            int x = col - viewport.left;

            Tile tile = tiles[row * width + col];

            if (!tile.visible) continue;

            mvaddch(y, x, tile.ch | COLOR_PAIR(tile.color));
        }
    }
}

Tile Level::getTile(int row, int col)
{
    return tiles[row * width + col];
}

void Level::setTile(int row, int col, Tile tile)
{
    tiles[row * width + col] = tile;
}

bool Level::inBounds(int row, int col)
{
    return (row >= 0 && row < height && col >= 0 && col < width);
}
