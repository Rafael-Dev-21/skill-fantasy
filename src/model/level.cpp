#include "level.hpp"
#include "../noise.hpp"
#include <cmath>

Tile::Tile(TileType type) :
	m_type(type)
{}

TileType Tile::getType()
{
	return m_type;
}

bool Tile::isType(TileType type)
{
	return m_type == type;
}

void Tile::setType(TileType type)
{
	m_type = type;
}



Level::Level()
{}

Tile Level::at(int y, int x)
{
	return m_tiles.at({ y, x });
}

void Level::genOverworld(Noise noise)
{
	for (int row = 0; row < LEVEL_SIZE; row++) {
		for (int col = 0; col < LEVEL_SIZE; col++) {
			float n = noise.perlin2d(row / 64.0f, col / 64.0f);
			TileType t = NO_TILE;

			if (n < 0.4) {
				t = TILE_WATER;
			} else if (n < 0.425) {
				t = TILE_SAND;
			} else if (n < 0.675) {
				t = TILE_GRASS;
			} else {
				t = TILE_STONE;
			}

			m_tiles.insert({ {row, col}, {t} });
		}
	}
}
