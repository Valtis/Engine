#include "Component/GraphicsComponent.h"
#include "Event/ChangeAnimationStateEvent.h"
#include <SDL_assert.h>



GraphicsComponent::GraphicsComponent() : 
	mIsAnimating(false), mGraphicsData(), mCurrentSprite(0), mCurrentAnimationID(0)
{

}

GraphicsComponent::~GraphicsComponent()
{

}

void GraphicsComponent::Update(double ticksPassed)
{
	if (mIsAnimating)
	{
		FrameData &data = mGraphicsData[mCurrentAnimationID][mCurrentSprite];
		data.mCurrentTickCount += ticksPassed;
		if (data.mCurrentTickCount > data.mTicksToNextFrame)
		{
			data.mCurrentTickCount = 0;
			NextSprite();
		}
	}
}

void GraphicsComponent::AddSprite(int animationID, int spriteID, int ticksToNextFrame)
{
	FrameData data;
	data.mCurrentTickCount = 0;
	data.mTicksToNextFrame  = ticksToNextFrame;
	data.spriteID = spriteID;
	mGraphicsData[animationID].push_back(data);
}

void GraphicsComponent::ClearSpriteIDs()
{
	mGraphicsData.clear();
}

int GraphicsComponent::GetCurrentSpriteID()
{
	SDL_assert(mGraphicsData[mCurrentAnimationID].size() > 0);
	SDL_assert((int)mGraphicsData[mCurrentAnimationID].size() >= mCurrentSprite);
	return mGraphicsData[mCurrentAnimationID][mCurrentSprite].spriteID;
}
	
void GraphicsComponent::NextSprite() 
{
	++mCurrentSprite;
	if (mCurrentSprite >= (signed int)mGraphicsData[mCurrentAnimationID].size())
	{
		mCurrentSprite = 0;
	}
}
void GraphicsComponent::PreviousSprite()
{
	--mCurrentSprite;
	if (mCurrentSprite < 0)
	{
		mCurrentSprite =  mGraphicsData[mCurrentAnimationID].size() - 1;
		SDL_assert(mCurrentSprite > 0);
	}
}
void GraphicsComponent::ResetSprite()
{
	mCurrentSprite = 0;
}

/*
void GraphicsComponent::HandleAnimationStateChangeEvent(Event *event)
{
	auto animationEvent = dynamic_cast<ChangeAnimationStateEvent *>(event);
	SDL_assert(animationEvent != nullptr);

	mCurrentAnimationID = animationEvent->GetAnimationID();
	mIsAnimating = animationEvent->GetNewAnimationState();
	if (!mIsAnimating)
	{
		ResetSprite();
	}

}*/