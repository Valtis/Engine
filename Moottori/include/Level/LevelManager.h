#pragma once
#include "Level/Level.h"
#include <vector>

class LevelManager
{
public:
	void AddLevel(int width, int height);
	Level *GetActiveLevel();

	void Update(double ticksPassed);

	static LevelManager &Instance();
	static void Release();
private:
	LevelManager() : mActiveLevelID(-1) { }
	static LevelManager *mInstance;
	int mActiveLevelID;
	std::vector<std::unique_ptr<Level>> mLevels;
};