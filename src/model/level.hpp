#pragma once

#include <functional>
#include <map>

#include "../events.hpp"
#include "../noise.hpp"
#include "object.hpp"

#define LEVEL_SIZE 2048

enum TileType {
	NO_TILE,
	TILE_GRASS,
	TILE_SAND,
	TILE_WATER,
	TILE_STONE,
	TILE_COUNT
};

class Tile {
public:
	Tile(TileType type = NO_TILE);
	~Tile() = default;

	TileType getType();
	bool isType(TileType type);
	void setType(TileType type);

private:
	TileType m_type;
	
	LooseObject *m_loose = nullptr;
	InstalledObject *m_installed = nullptr;
};

class Level {
public:
	Level();
	~Level() = default;

	Tile at(int y, int x);
	void genOverworld(Noise noise);

private:

	std::map<std::pair<int, int>, Tile> m_tiles;
};
