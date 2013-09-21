#pragma once

#include "Utility/LuaState.h"

class Level
{
public:
	Level() { }
	void AddEntity(int id) { mLevelEntities.push_back(id); }
	void Update(double ticksPassed);

private:
	void UpdateEntities(double ticksPassed);

	int mWidth;
	int mHeight;
	std::vector<int> mLevelEntities;
	LuaState mLuaState; 
};
