#include "Component/AccelerationComponent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/QueryDirectionEvent.h"
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
	double velocityChange = mMaxAcceleration;
	if (changeEvent->GetState() == UIEventState::Stop)
	{
		velocityChange = 0;
	}
	switch (changeEvent->GetDirection())
	{
		case Direction::Forward:
		case Direction::Backward:
			HandleForwardBackwardMovement(changeEvent->GetDirection(), velocityChange);
			break;
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

	double velocityChange = mMaxRotationAcceleration;
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

#include <fstream>

void AccelerationComponent::HandleForwardBackwardMovement(Direction direction, double velocityChange)
{
	// need direction to calculate proper xy-vectors
	// query it
	double rotation = 0;
	bool wasHandled = false;
	GetEventHandler().ProcessEvent(std::unique_ptr<QueryDirectionEvent>(new QueryDirectionEvent(rotation, wasHandled)));

	if (!wasHandled)
	{
		return;
	}
	// shift rotation: currently 0 degrees is upwards, we want it to be on x axis
	rotation -= 180;
	// after this x-axis is mirrored; we need to multiply the acceleration with -1 to rectify this
	
	double multiplier = 1;
	if (direction == Direction::Backward)
	{
		multiplier = -1;
	}
	std::ofstream file("debug.txt", std::ios::app);

	mCurrentXAcceleration = -1*multiplier*velocityChange*sin(rotation*3.1415926535/180.0);
	mCurrentYAcceleration = multiplier*velocityChange*cos(rotation*3.1415926535/180.0);
	file << "angle: " << rotation << "\tx-accel: " <<  mCurrentXAcceleration << "\ty-accel: " << mCurrentYAcceleration << "\n";
}