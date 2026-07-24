#include "ModeData.hpp"
#ifdef USE_GUILE
extern "C" {
//#include "../api/guile_api.h"
void  skfantasy_api_guile_update(World *, Creature *);
};
#endif

using Dir = Direction;

using namespace ftxui;

#define BLOCK_LENGTH 10
#define CTRL(c) ((c)&0x1f)

static Element render_help()
{
  return vbox({
  	text("(r)egen"),
  	text("ESC back"),
  	text("hjkl move"),
  	text("(p)lace"),
  	text("(b)reak")
  });
}

static Element render_stats(Creature const * const creature)
{
  return vbox({
	  text(std::format("STR: {}", get_stat_value(creature, STAT_STR))),
	  text(std::format("MBL: {}", get_stat_value(creature, STAT_MBL))),
	  text(std::format("MND: {}", get_stat_value(creature, STAT_MND))),
	  text(std::format("FTH: {}", get_stat_value(creature, STAT_FTH))),
	  text(std::format("HRT: {}", get_stat_value(creature, STAT_HRT)))
  });
}

Element PlayMode::render(ScreenInteractive& screen)
{
  auto& player = data.world->creatures.get(data.player);
  return vbox({
      render_help(),
      separator(),
      render_world(data.world.get(), player.position, screen.dimx(), screen.dimy()-13),
      separator(),
      render_stats(&player)
  });
}

bool PlayMode::handle(Event event, ScreenInteractive& screen)
{
	if (data.player == Handle{} || data.world == NULL) {
    screen.Exit();
		return true;
	}

  auto& fac = *data.factory;
  auto& player = data.world->creatures.get(data.player);

	Dir old_dir = player.facing;
	Point cell = player.position;
	
	move_from(&cell, player.facing);

  if (world_update(data.world.get(), data.player)) {
    screen.Exit();
    return true;
  }

#ifdef USE_GUILE
  skfantasy_api_guile_update(data.world, data.player);
#endif

  if (
       event == Event::Character('l')
    || event == Event::Character('k')
    || event == Event::Character('j')
    || event == Event::Character('h')
  ) {
		player.facing = dir_from_ch(event.character()[0], player.facing);
		if (player.facing == old_dir) {
			creature_move_by(&player, data.world.get());
    }
  } else if (
      event == Event::Character('p')
  ) {
    place_wall(data.world.get(), cell);
  } else if (
      event == Event::Character('q')
  ) {
    break_wall(data.world.get(), cell);
  } else if (
      event == Event::Character('f')
  ) {
    fac.makeFire(cell);
  } else if (
      event == Event::CtrlF
  ) {
    try_toil(data.world.get(), cell);
  } else if (
      event == Event::Character('r')
  ) {
    data.setMode(std::make_unique<GenMode>(data));
  } else if (
      event == Event::Escape
  ) {
/*    free_world(data.world);
    data.world = nullptr;*/
    data.world.reset();
    data.player = {};
    data.factory = {};
    data.setMode(std::make_unique<StartMode>(data));
  }
  return false;
}
