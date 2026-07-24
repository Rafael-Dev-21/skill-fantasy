#include "ModeData.hpp"

TileType tile_types[TILE_COUNT] = {
	{ ' ', colorpack(255,255,255) },
	{ ',', colorpack(15,198,35) },
	{ '~', colorpack(198,198,15) },
	{ '7', colorpack(30, 50, 70) },
	{ '.', colorpack(115, 155, 155) },
  { .glyph='3', .color=colorpack(198,35,15), .highmoist = {true, 1, TILE_MUD} },
  { .glyph='3', .color=colorpack(115,115,15), .lowmoist = {true, 0, TILE_SOIL} },
};

ObjectType obj_types[OBJ_COUNT] = {
	{ -1, colorpack(0,0,0), false, false },
	{ '#', colorpack(135,135,135), true, true },
  { '*', colorpack(203, 45,35), false, true },
  { .glyph=',', .color=colorpack(198,203,70), .solid=true, .flammable=true, .grow = { true, 32, OBJ_WHEAT } },
  { '1', colorpack(203,203,70), true, true },
};
