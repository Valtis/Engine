#include "Graphics/SpriteManager.h"

SpriteManager *SpriteManager::mInstance = nullptr;

SpriteManager::SpriteManager() 
{

}

SpriteManager::~SpriteManager()
{

}

SpriteManager &SpriteManager::Instance()
{
	if (mInstance == nullptr)
	{
		mInstance = new SpriteManager();
	}

	return *mInstance;
}

void SpriteManager::Release()
{
	delete mInstance;
	mInstance = nullptr;
}

void SpriteManager::LoadSprites(std::string datafilePath)
{

}

Sprite *SpriteManager::GetSprite(UniqueID id)
{
	if (mSprites.count(id) == 0)
	{
		return nullptr;
	}

	return mSprites[id].get();
}