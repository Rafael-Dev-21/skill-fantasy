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
	return m_tiles.at(y).at(x);
}

void Level::genOverworld(Noise noise)
{
	for (int row = 0; row < LEVEL_SIZE; row++) {
		for (int col = 0; col < LEVEL_SIZE; col++) {
			float n = noise.perlin2d(row / 32.0f, col / 32.0f);

			if (n < 0.4) {
				m_tiles[row][col].setType(TILE_WATER);
			} else if (n < 0.425) {
				m_tiles[row][col].setType(TILE_SAND);
			} else if (n < 0.675) {
				m_tiles[row][col].setType(TILE_GRASS);
			} else {
				m_tiles[row][col].setType(TILE_STONE);
			}
		}
	}
}
