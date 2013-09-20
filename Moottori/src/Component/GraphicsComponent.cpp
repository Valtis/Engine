#include "Component/GraphicsComponent.h"
#include "Event/ChangeAnimationStateEvent.h"
#include <SDL_assert.h>

GraphicsComponent::GraphicsComponent(std::vector<int> spriteIDs) : 
	mIsAnimating(false), mGraphicsData(), mCurrentSprite(0), mCurrentAnimationID(0)
{
	// test code
	// todo: replace 
	for (int id : spriteIDs)
	{
		FrameData frameData;
		frameData.spriteID = id;
		frameData.mTicksToNextFrame = 5; // test value
		frameData.mCurrentTickCount = 0;
		mGraphicsData[0].push_back(frameData);
	}
}

GraphicsComponent::GraphicsComponent() : 
	mIsAnimating(false), mGraphicsData(), mCurrentSprite(0), mCurrentAnimationID(0)
{

}

GraphicsComponent::~GraphicsComponent()
{

}

void GraphicsComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeAnimationState, 
		[&](Event *event) { this->HandleAnimationStateChangeEvent(event); } );
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

void GraphicsComponent::AddSpriteID(int id)
{
	FrameData data;
	data.mCurrentTickCount = 0;
	data.mTicksToNextFrame  = 0;
	data.spriteID = id;
	mGraphicsData[0].push_back(data);
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


void GraphicsComponent::HandleAnimationStateChangeEvent(Event *event)
{
	auto animationEvent = dynamic_cast<ChangeAnimationStateEvent *>(event);
	SDL_assert(animationEvent != nullptr);

	mIsAnimating = animationEvent->GetNewAnimationState();
	if (!mIsAnimating)
	{
		ResetSprite();
	}

}