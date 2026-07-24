#ifdef _MSC_VER
# define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

#include "ModeData.hpp"
extern "C" {
#ifdef USE_GUILE
//#include "api/guile_api.h"
extern void skfantasy_api_guile_init();
#endif
}

using namespace ftxui;

int main(int argc, char *argv[])
{
  auto screen = ScreenInteractive::Fullscreen();

#ifndef VERSION
	ModeData data = {{}, new World(), {}};

  std::ifstream ifversion{"version.txt"};
  if (!std::getline(ifversion, data.version)) {
    throw std::runtime_error("Version file missing");
  }
#else
  const char *v = VERSION;
  ModeData data = {{}, new World(), std::string(v)};
#endif
  
  time_t seed = time(NULL);
  srand(*(int*)&seed);

#ifdef USE_GUILE
  skfantasy_api_guile_init();
#endif

  auto app = Renderer([&] {
      return data.mode->render(screen);
  });
  app |= CatchEvent([&](Event event) {
      return data.mode->handle(event, screen);
  });

  screen.Loop(app);
/*
	int mode = 0;
	init_curses();
	while (mode != -1) {
		switch (mode) {
		case 0:
			mode = start_mode(&data);
			break;
		case 1:
			mode = generate_mode(&data);
			break;
		case 2:
			mode = play_mode(&data);
			break;
		}
	}
	end_curses();
*/
	return EXIT_SUCCESS;
}

