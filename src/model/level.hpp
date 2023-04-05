#pragma once

#include <functional>
#include <vector>
#include <array>

#include "../events.hpp"
#include "../noise.hpp"
#include "object.hpp"

#define LEVEL_SIZE 1024

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

	std::array<std::array<Tile, LEVEL_SIZE>, LEVEL_SIZE> m_tiles;
};
