#include "Component/VelocityComponent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeLocationEvent.h"

#include <SDL_assert.h>
#include <cmath>

#define SIGNUM(x) ((x) < 0) ? -1 : ((x) > 0)

VelocityComponent::VelocityComponent(double maxVelocity, double maxRotationSpeed, double velocityLossPerTick, double rotationVelocityLossPerTick) 
	: mCurrentXVelocity(0), mCurrentYVelocity(0), mCurrentRotationSpeed(0), mMaxVelocity(maxVelocity), mMaxRotationSpeed(maxRotationSpeed), 
	mVelocityLossPerTick(velocityLossPerTick), mRotationVelocityLossPerTick(rotationVelocityLossPerTick)
{

}

VelocityComponent::~VelocityComponent()
{

}

void VelocityComponent::Update(double ticksPassed)
{
	if (mCurrentRotationSpeed != 0 || mCurrentXVelocity != 0 || mCurrentYVelocity != 0)
	{
		GetEventHandler().ProcessEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(mCurrentXVelocity*ticksPassed, mCurrentYVelocity*ticksPassed, mCurrentRotationSpeed*ticksPassed)));
		DecaySpeed();
	}
}

void VelocityComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeVelocity, [&](Event *event) { this->HandleVelocityChangeEvents(event); });
}

void VelocityComponent::DecaySpeed() 
{
	
	int xSign = SIGNUM(mCurrentXVelocity);
	int ySign = SIGNUM(mCurrentYVelocity);
	mCurrentXVelocity = fabsf(mCurrentXVelocity) - mVelocityLossPerTick;
	mCurrentYVelocity = fabsf(mCurrentYVelocity) - mVelocityLossPerTick;
	
	if (mCurrentXVelocity < 0)
	{
		mCurrentXVelocity = 0;
	}
	if (mCurrentYVelocity < 0)
	{
		mCurrentYVelocity = 0;
	}

	mCurrentXVelocity *= xSign;
	mCurrentYVelocity *= ySign;


	int rotateSign = SIGNUM(mCurrentRotationSpeed);
	mCurrentRotationSpeed = fabsf(mCurrentRotationSpeed) - mRotationVelocityLossPerTick;
	if (mCurrentRotationSpeed < 0)
	{
		mCurrentRotationSpeed = 0;
	}

	mCurrentRotationSpeed *= rotateSign;
}


void VelocityComponent::HandleVelocityChangeEvents(Event *event)
{
	ChangeVelocityEvent *changeEvent = dynamic_cast<ChangeVelocityEvent *>(event);
	SDL_assert(changeEvent != nullptr);

	mCurrentXVelocity += changeEvent->GetXVelocityChange();
	mCurrentYVelocity += changeEvent->GetYVelocityChange();
	mCurrentRotationSpeed += changeEvent->GetRotationChange();

	int xSign = SIGNUM(mCurrentXVelocity);
	int ySign = SIGNUM(mCurrentYVelocity);
	int rotateSign = SIGNUM(mCurrentRotationSpeed);

	if (fabsf(mCurrentXVelocity) > mMaxVelocity)
	{
		mCurrentXVelocity = mMaxVelocity*xSign;
	}

	if (fabsf(mCurrentYVelocity) > mMaxVelocity)
	{
		mCurrentYVelocity = mMaxVelocity*ySign;
	}

	if (fabsf(mCurrentRotationSpeed) > mMaxRotationSpeed)
	{
		mCurrentRotationSpeed = mMaxRotationSpeed*rotateSign;
	}

}