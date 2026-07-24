#include <optional>
#include <memory>
#include <string>

#include "skfantasy.hpp"

#include <ftxui/component/screen_interactive.hpp>

template<typename T, typename DT=std::default_delete<T>>
using Maybe = std::unique_ptr<T, DT>;

struct BaseMode;
struct StartMode;

struct WorldDeleter {
  void operator()(World* w)
  {
    free_world(w);
  }
};

struct ModeData {
  CreatureHandle player;
  Maybe<World, WorldDeleter> world;
  std::string version;
  std::unique_ptr<BaseMode> mode;
  std::optional<CreatureFactory> factory{};

  ModeData(CreatureHandle player, World* world, std::string version);
  void setMode(std::unique_ptr<BaseMode> m); 
};

struct BaseMode {
  ModeData& data;
  BaseMode(ModeData& data) :
    data(data)
  {}
  virtual ~BaseMode() = default;
  virtual bool handle(ftxui::Event event, ftxui::ScreenInteractive& screen) = 0;
  virtual ftxui::Element render(ftxui::ScreenInteractive& screen) = 0;
};

struct StartMode: public BaseMode {
  StartMode(ModeData& data) :
    BaseMode(data)
  {}
  virtual ~StartMode() = default;
  virtual bool handle(ftxui::Event event, ftxui::ScreenInteractive& screen) override;
  virtual ftxui::Element render(ftxui::ScreenInteractive& screen) override;
};

struct GenMode: public BaseMode {
  GenMode(ModeData& data) :
    BaseMode(data)
  {}
  virtual ~GenMode() = default;
  virtual bool handle(ftxui::Event event, ftxui::ScreenInteractive& screen) override;
  virtual ftxui::Element render(ftxui::ScreenInteractive& screen) override;
};

struct PlayMode: public BaseMode {
  PlayMode(ModeData& data) :
    BaseMode(data)
  {}
  virtual ~PlayMode() = default;
  virtual bool handle(ftxui::Event event, ftxui::ScreenInteractive& screen) override;
  virtual ftxui::Element render(ftxui::ScreenInteractive& screen) override;
};

ftxui::Element render_world(World const * const World, Point center, int width, int height);
