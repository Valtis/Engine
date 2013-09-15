#include "Component/AccelerationComponent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/ChangeVelocityEvent.h"
#include <cmath>
#include "SDL_assert.h"

void AccelerationComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeAcceleration, [&](Event *event) { this->HandleAccelerationChangeEvents(event); } );
}


void AccelerationComponent::Update(double ticksPassed) 
{
	if (mCurrentXAcceleration != 0 || mCurrentYAcceleration !=0 || mCurrentRotationAcceleration != 0)
	{
		GetEventHandler().ProcessEvent(std::unique_ptr<ChangeVelocityEvent>(new ChangeVelocityEvent(mCurrentXAcceleration*ticksPassed, 
			mCurrentYAcceleration*ticksPassed, mCurrentRotationAcceleration*ticksPassed)));
	}

}

void AccelerationComponent::HandleAccelerationChangeEvents(Event *event)
{
	ChangeAccelerationEvent *changeEvent = dynamic_cast<ChangeAccelerationEvent *>(event);
	SDL_assert(changeEvent != nullptr);

	GetXYVelocity(changeEvent);
	GetTurnSpeed(changeEvent);

}

void AccelerationComponent::GetXYVelocity(ChangeAccelerationEvent *changeEvent)
{
	int velocityChange = mMaxAcceleration;
	if (changeEvent->GetState() == UIEventState::Stop)
	{
		velocityChange = 0;
	}
	switch (changeEvent->GetDirection())
	{
	case Direction::Up:
		mCurrentYAcceleration = -velocityChange;
		break;

	case Direction::TopRight:
		mCurrentXAcceleration = sqrt(velocityChange);
		mCurrentYAcceleration = -sqrt(velocityChange);
		break;
	case Direction::Right:
		mCurrentXAcceleration = velocityChange;
		break;

	case Direction::BottomRight:
		mCurrentXAcceleration = sqrt(velocityChange);
		mCurrentYAcceleration = sqrt(velocityChange);
		break;

	case Direction::Bottom:
		mCurrentYAcceleration = velocityChange;
		break;

	case Direction::BottomLeft:
		mCurrentXAcceleration = -sqrt(velocityChange);
		mCurrentYAcceleration = sqrt(velocityChange);
		break;

	case Direction::Left:
		mCurrentXAcceleration  =-velocityChange;
		mCurrentYAcceleration = 0;
		break;
	case Direction::TopLeft:
		mCurrentXAcceleration = -sqrt(velocityChange);
		mCurrentYAcceleration = -sqrt(velocityChange);
		break;
	default:
		break;
	}
}


void AccelerationComponent::GetTurnSpeed(ChangeAccelerationEvent *changeEvent)
{

	int velocityChange = mMaxRotationAcceleration;
	if (changeEvent->GetState() == UIEventState::Stop)
	{
		velocityChange = 0;
	}

	switch (changeEvent->GetTurnDirection())
	{

	case Direction::Right:
		mCurrentRotationAcceleration = velocityChange;
		break;

	case Direction::Left:
		mCurrentRotationAcceleration = -velocityChange;
		break;
	default:
		break;
	}
}