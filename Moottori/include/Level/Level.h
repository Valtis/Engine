#pragma once

#include "Utility/LuaState.h"

class Level
{
public:
	Level() : mWidth(0), mHeight(0) { }
	Level(int width, int height) : mWidth(width), mHeight(height) { }

	void AddEntity(int id) { mLevelEntities.push_back(id); }
	void Update(double ticksPassed);

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }


private:
	void UpdateEntities(double ticksPassed);

	int mWidth;
	int mHeight;
	std::vector<int> mLevelEntities;
	LuaState mLuaState; 
};
