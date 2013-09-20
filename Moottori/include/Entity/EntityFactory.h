#pragma once

#include <memory>
#include <vector>
#include "Utility/UniqueID.h"

class Entity;
class UI;
namespace EntityFactory
{
	std::unique_ptr<Entity> CreatePlayer(int x, int y, double maxVelocity, double maxRotationSpeed, 
		double maxRotationAcceleration, double maxRotation, std::vector<int> spriteIDs, UI &ui);
}