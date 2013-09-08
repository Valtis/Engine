#include "Component/GraphicsComponent.h"
#include <SDL.h>

GraphicsComponent::GraphicsComponent(std::vector<UniqueID> spriteIDs) : mSpriteIDs(spriteIDs), mCurrentSprite(0)
{
}

GraphicsComponent::GraphicsComponent() : mSpriteIDs(), mCurrentSprite(0)
{

}

GraphicsComponent::~GraphicsComponent()
{

}

void GraphicsComponent::AddSpriteID(UniqueID id)
{
	mSpriteIDs.push_back(id);
}

void GraphicsComponent::ClearSpriteIDs()
{
	mSpriteIDs.clear();
}

UniqueID GraphicsComponent::GetCurrentSpriteID()
{
	SDL_assert(mSpriteIDs.size() > 0);
	SDL_assert(mSpriteIDs.size() >= mCurrentSprite);
	return mSpriteIDs[mCurrentSprite];
}
	
void GraphicsComponent::NextSprite() 
{
	++mCurrentSprite;
	if (mCurrentSprite >= (signed int)mSpriteIDs.size())
	{
		mCurrentSprite = 0;
	}
}
void GraphicsComponent::PreviousSprite()
{
	--mCurrentSprite;
	if (mCurrentSprite < 0)
	{
		mCurrentSprite =  mSpriteIDs.size() - 1;
		SDL_assert(mCurrentSprite > 0);
	}
}
void GraphicsComponent::ResetSprite()
{
	mCurrentSprite = 0;
}
