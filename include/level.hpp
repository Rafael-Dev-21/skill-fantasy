#pragma once

#include <vector>
#include "geom.hpp"

enum class TileType {
	GRASS,
	WATER,
	SAND,
	STONE
};

struct Tile {
	Tile(TileType type = TileType::GRASS);

	TileType type;
	int sprite;
	int colors;
};

class Level {
public:
	Level(int width = 128, int height = 128);

	Tile tileAt(int x, int y);

	void render(IVector cameraOrigin);

	IPoint getSpawn();

	bool inBounds(int x, int y);

private:
	void genWorld();
	TileType getTile(float e);
	int indexOf(int x, int y);

	std::vector<Tile> tiles;
	int width;
	int height;

	IPoint spawn;
};
