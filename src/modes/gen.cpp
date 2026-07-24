#include "ModeData.hpp"

using namespace ftxui;

Element GenMode::render(ScreenInteractive& screen)
{
  return vbox({
      text("Generating..."),
      separator(),
      text("[Press any key]")
  });
}

bool GenMode::handle(Event event, ScreenInteractive& screen)
{
	if (data.world) {
		data.world.reset();
	}

	data.world.reset(create_world(128, 128));
	init_world(data.world.get(), rand());
  data.factory = CreatureFactory(data.world.get());
  auto& fac = *data.factory;
	data.player = fac.makePlayer(); //create_player(data.world);

	for (int i = 0; i < 8; i++) {
		//create_fungi(data.world);
    fac.makeFungi();
	}

  for (int i = 0; i < 24; i++) {
    //create_bat(data.world);
    fac.makeBat();
  }

  data.setMode(std::make_unique<PlayMode>(data));

  return false;
}
