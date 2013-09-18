#include "Component/VelocityComponent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/ChangeAnimationStateEvent.h"

#include <SDL_assert.h>
#include <cmath>

#define SIGNUM(x) (((x) < 0) ? -1 : ((x) > 0))

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
	bool animationState = false;
	if (mCurrentRotationSpeed != 0 || mCurrentXVelocity != 0 || mCurrentYVelocity != 0)
	{
		GetEventHandler().ProcessEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(mCurrentXVelocity*ticksPassed, mCurrentYVelocity*ticksPassed, mCurrentRotationSpeed*ticksPassed)));
		animationState = true;
		DecaySpeed();
	}

	GetEventHandler().AddEvent(
		std::unique_ptr<ChangeAnimationStateEvent>(
		new ChangeAnimationStateEvent(animationState)));
}

void VelocityComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeVelocity, [&](Event *event) { this->HandleVelocityChangeEvents(event); });
}

void VelocityComponent::DecaySpeed() 
{

		
	double angle = atan2(mCurrentYVelocity, mCurrentXVelocity);
	

	double mTotalVelocity = sqrt(mCurrentXVelocity*mCurrentXVelocity + mCurrentYVelocity*mCurrentYVelocity) - mVelocityLossPerTick;
	if (mTotalVelocity < 0)
	{
		mTotalVelocity = 0;
	}
	
	mCurrentXVelocity = fabs(mTotalVelocity)*cos(angle);
	mCurrentYVelocity = fabs(mTotalVelocity)*sin(angle);

	int rotSign = SIGNUM(mCurrentRotationSpeed);
	mCurrentRotationSpeed = fabs(mCurrentRotationSpeed) - mRotationVelocityLossPerTick;
	if (mCurrentRotationSpeed < 0)
	{
		mCurrentRotationSpeed = 0;
	}

	mCurrentRotationSpeed *= rotSign;
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