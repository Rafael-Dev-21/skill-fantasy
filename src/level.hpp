#pragma once

#include <vector>

#define MAP_SIZE 128

struct Rect {
    int top, left, bottom, right;
};

struct Tile {
    int color;
    bool visible;
    bool solid;
    char ch;
};

class Level {
public:
    Level(int width, int height);
    ~Level();

    void genOverworld();
    void render(Rect view);

    int getWidth();
    int getHeight();

    Tile getTile(int col, int row);
    void setTile(int col, int row, Tile tile);

    bool inBounds(int row, int col);

private:
    int width, height;
    std::vector<Tile> tiles;
};
