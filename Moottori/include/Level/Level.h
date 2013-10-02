#pragma once

#include "Utility/LuaState.h"

class Level
{
public:
	Level();
	Level(int width, int height);

	void AddEntity(int id) { mLevelEntities.push_back(id); }
	void Update(double ticksPassed);

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	std::vector<int> GetEntities() { return mLevelEntities; }

	void InitializeLuaState();

private:
	void UpdateEntities(double ticksPassed);
	
	int mWidth;
	int mHeight;
	std::vector<int> mLevelEntities;
};
