#pragma once

#include <memory>
#include <vector>
class Entity;
class UI;
namespace EntityFactory
{
	std::unique_ptr<Entity> CreatePlayer(int x, int y, std::vector<int> spriteIDs, UI &ui);
}