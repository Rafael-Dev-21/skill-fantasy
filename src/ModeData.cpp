#include "ModeData.hpp"

ModeData::ModeData(CreatureHandle player, World* world, std::string version) :
    player(std::move(player)), world(std::move(world)), version(version)
  {
    mode = std::make_unique<StartMode>(*this);
  }


void ModeData::setMode(std::unique_ptr<BaseMode> m)
{
  mode = std::move(m);
}
