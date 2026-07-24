#include "ModeData.hpp"

using namespace ftxui;
Element StartMode::render(ScreenInteractive& screen)
{
  return vbox({
	text(std::format("SKILL FANTASY {}", data.version)),
  separator(),
	text("(s)tart"),
	text("ESC for quit")
  });
}

bool StartMode::handle(Event event, ScreenInteractive& screen) {
  if (event == Event::Escape) {
    screen.Exit();
    return true;
  }
  if (event == Event::Character('s')) {
    data.setMode(std::move(std::make_unique<GenMode>(data)));
  }
	return false;
}
