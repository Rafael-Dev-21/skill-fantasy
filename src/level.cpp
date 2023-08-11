#include "level.hpp"
#include "noise.hpp"
#include "math.hpp"

#include <ncurses.h>

Tile::Tile(TileType type) :
	type(type)
{
	switch (type) {
	case TileType::GRASS:
		sprite = ',';
		colors = 1;
		break;
	case TileType::SAND:
		sprite = '~';
		colors = 2;
		break;
	case TileType::WATER:
		sprite = '~';
		colors = 3;
		break;
	case TileType::STONE:
		sprite = '.';
		colors = 4;
	}
}

Level::Level(int width, int height) :
	width(width),
	height(height)
{
	tiles.resize(width * height);
	genWorld();
}

Tile Level::tileAt(int x, int y)
{
	return tiles[indexOf(x, y)];
}

void Level::render(IVector cameraOrigin)
{
	for (int y = 0; y < LINES; y++) {
		for (int x = 0; x < COLS; x++) {
			int mapx = x + cameraOrigin.x;
			int mapy = y + cameraOrigin.y;

			if (inBounds(mapx, mapy)) {
				auto tile = tileAt(mapx, mapy);
				int graphic = tile.sprite |
					COLOR_PAIR(tile.colors);
				mvaddch(y, x, graphic);
			} else {
				mvaddch(y, x, ' ');
			}
		}
	}
}

IPoint Level::getSpawn()
{
	return spawn;
}

bool Level::inBounds(int x, int y)
{
	return x >= 0 && x < width && y >= 0 && y < height;
}

void Level::genWorld()
{
	bool spawnSet = false;

	float size = 32.0;

	FBMParams params;

	params.amplitude = 1;
	params.persistence = 1.0 / 3.0;
	params.frequency = 1;
	params.lacunarity = 3.0;
	params.octaves = 10;

	Perlin noise;

	float limit = sqrt(0.5);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float nx = x / size - 0.5;
			float ny = y / size - 0.5;

			float e = noise.fbm(nx, ny, params);
			e = Math::normalize(e, -limit, limit);
			e = std::round(e * 12.0);

			TileType type = getTile(e);

			if (type != TileType::WATER && !spawnSet) {
				spawn.x = x;
				spawn.y = y;
				spawnSet = true;
			}

			tiles[indexOf(x, y)] = Tile(type);
		}
	}
}

TileType Level::getTile(float e)
{
	if (e < 5)
		return TileType::WATER;
	else if (e < 6)
		return TileType::SAND;
	else if (e < 10)
		return TileType::GRASS;
	else
		return TileType::STONE;
}

int Level::indexOf(int x, int y)
{
	return y * width + x;
}
