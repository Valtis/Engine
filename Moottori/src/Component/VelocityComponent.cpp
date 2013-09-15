#include "Component/VelocityComponent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeLocationEvent.h"

#include <SDL_assert.h>
#include <cmath>

#define SIGNUM(x) ((x) < 0) ? -1 : ((x) > 0)

VelocityComponent::VelocityComponent(double maxVelocity, double maxRotationSpeed, double velocityLossPerTick, double rotationVelocityLossPerTick) 
	: mCurrentXVelocity(0), mCurrentYVelocity(0), mCurrentRotationSpeed(0), mMaxVelocity(maxVelocity), mMaxRotationSpeed(maxRotationSpeed), 
	mVelocityLossPerTick(velocityLossPerTick), mRotationVelocityLossPerTick(mRotationVelocityLossPerTick)
{

}

VelocityComponent::~VelocityComponent()
{

}

void VelocityComponent::Update(double ticksPassed)
{
	if (mCurrentRotationSpeed > 0 || mCurrentXVelocity > 0 || mCurrentYVelocity > 0)
	{
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(mCurrentXVelocity, mCurrentYVelocity, mCurrentRotationSpeed)));
		DecaySpeed();
	}
}

void VelocityComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeVelocity, [&](Event *event) { this->HandleVelocityChangeEvents(event); });
}

void VelocityComponent::DecaySpeed() 
{
	double angle = 0;
	if (fabsf(mCurrentXVelocity) < 0.01)	
	{
		angle = 0;

	}
	else 
	{
		angle = atan(fabsf(mCurrentYVelocity)/fabsf(mCurrentXVelocity));

	}
	int xSign = SIGNUM(mCurrentXVelocity);
	int ySign = SIGNUM(mCurrentYVelocity);
	mCurrentXVelocity -= xSign*mVelocityLossPerTick*cos(angle);
	mCurrentYVelocity -= ySign*mVelocityLossPerTick*sin(angle);

	if (SIGNUM(mCurrentXVelocity) != xSign)
	{
		mCurrentXVelocity = 0;
	}

	if (SIGNUM(mCurrentYVelocity) != ySign)
	{
		mCurrentYVelocity = 0;
	}

	int rotateSign = SIGNUM(mCurrentRotationSpeed);
	mCurrentRotationSpeed -= rotateSign*mRotationVelocityLossPerTick;
	if (SIGNUM(mCurrentRotationSpeed) != rotateSign)
	{
		mCurrentRotationSpeed = 0;
	}

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
		mCurrentXVelocity = mMaxVelocity*ySign;
	}

	if (fabsf(mCurrentRotationSpeed) > mMaxRotationSpeed)
	{
		mCurrentRotationSpeed = mMaxRotationSpeed*ySign;
	}

}