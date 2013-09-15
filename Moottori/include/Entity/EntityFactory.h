#pragma once

#include <memory>
#include <vector>
#include "Utility/UniqueID.h"

class Entity;
class UI;
namespace EntityFactory
{
	std::unique_ptr<Entity> CreatePlayer(int x, int y, int velocity, double turnVelocity, std::vector<int> spriteIDs, UI &ui);
}