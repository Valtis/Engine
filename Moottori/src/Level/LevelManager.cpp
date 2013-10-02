#include "Level/LevelManager.h"
#include <SDL_assert.h>
LevelManager *LevelManager::mInstance = nullptr;


LevelManager &LevelManager::Instance()
{
	if (mInstance == nullptr)
	{
		mInstance = new LevelManager();
	}

	return *mInstance;
}

void LevelManager::Release()
{
	delete mInstance;
	mInstance = nullptr;
}

Level *LevelManager::GetActiveLevel()
{
	if (mActiveLevelID == -1)
	{
		return nullptr;
	}

	SDL_assert_release(mActiveLevelID >= 0 && mActiveLevelID < mLevels.size());
	return mLevels[mActiveLevelID].get();
}

void LevelManager::AddLevel(int width, int height)
{
	std::unique_ptr<Level> level(new Level(width, height));
	mLevels.push_back(std::move(level));
	
	if (mActiveLevelID == -1)
	{
		mActiveLevelID = 0;
	}
}

void LevelManager::Update(double ticksPassed)
{
	if (mActiveLevelID != -1)
	{
		SDL_assert_release(mActiveLevelID >= 0 && mActiveLevelID < mLevels.size());
		mLevels[mActiveLevelID]->Update(ticksPassed);
	}
}