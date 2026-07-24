#include "ModeData.hpp"

using namespace ftxui;

struct DrawCell {
  char glyph;
  Color color;
};

void draw_creature(std::vector<DrawCell>& fb, Creature const * const creature, Point player, int width, int height)
{
	Point center = { (int16_t)(width / 2), (int16_t)(height / 2) };
	Point cursor = {0,0};

	if (creature == NULL) {
		return;
	}
	
	Point pos = creature->position;
	cursor = point_from_dir(creature->facing);

	Point modified_pos = { (int16_t)(center.x + pos.x - player.x), (int16_t)(center.y + pos.y - player.y) };

	Point cell = { (int16_t)(cursor.x + modified_pos.x), (int16_t)(cursor.y + modified_pos.y) };

	if (cell.x >= 0 && cell.y >= 0
	 && cell.x < width && cell.y < height) {
    fb[cell.x + cell.y * width].glyph = 'x';
    fb[cell.x + cell.y * width].color = Color::White;
  }
  auto mp = modified_pos;
	if (mp.x >= 0 && mp.y >= 0
	 && mp.x < width && mp.y < height) {
    fb[modified_pos.x + modified_pos.y * width].glyph = creature->glyph;
    fb[modified_pos.x + modified_pos.y * width].color = colorupack(creature->color);
  }
//  attron(COLOR_PAIR(creature->color));
//	mvaddch(modified_pos.y, modified_pos.x, creature->glyph);
//  attroff(COLOR_PAIR(creature->color));
}

void draw_creatures(std::vector<DrawCell>& fb, World * world, Point center, int width, int height)
{
//	Creature *it = world->creatures;

  for (auto& it : world->creatures) {
//	while (it != NULL) {
    if (it.handle != Handle{}) {
		  draw_creature(fb, &it, center, width, height);
    }
//		it = it->next;
	}
}

void draw_tiles(std::vector<DrawCell>& fb, World const * const world, Point center, int width, int height)
{
	if (world == NULL) {
		return;
	}

	int startx = center.x - width/2;
	int starty = center.y - height/2;

	for (int row = 0; row < height; row += 1) {
		for (int col = 0; col < width; col += 1) {
      auto& dc = fb[col + row * width];
      dc.color = Color::White;
			int mapx = startx + col;
			int mapy = starty + row;
			if (mapx < 0 || mapy < 0
				|| mapx >= world->width || mapy >= world->height) {

				dc.glyph = ' ';
				continue;
			}

			int sprite = ' ', color = 0;
			auto& tile = world->tiles[mapy*world->width+mapx];
			TileType& tile_type = tile_types[tile.type];
			ObjectType& obj_type = obj_types[tile.object];

			if (obj_type.glyph != -1) {
				sprite = obj_type.glyph;
        color = obj_type.color;
      } else {
				sprite = tile_type.glyph;
        color = tile_type.color;
      }

      dc.glyph = sprite;
      dc.color = colorupack(color);
		}
	}
}

Element render_world(World const * const world, Point center, int width, int height)
{
  std::vector<DrawCell> framebuffer(width * height);
  draw_tiles(framebuffer, world, center, width, height);
  draw_creatures(framebuffer, (World*)world, center, width, height);

  Elements rows;
  for (int row = 0; row < height; row++) {
    Elements cols;
    for (int col = 0; col < width; col++) {
      int idx = col + row * width;
      DrawCell dc = framebuffer[idx];
      cols.push_back(text(std::string(1, dc.glyph)) | color(dc.color));
    }
    rows.push_back(hbox(cols));
  }
  return vbox(rows);
}

