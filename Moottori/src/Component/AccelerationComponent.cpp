#include "Component/AccelerationComponent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/ChangeVelocityEvent.h"
#include <cmath>
#include "SDL_assert.h"

void AccelerationComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeAcceleration, [&](Event *event) { this->HandleAccelerationChangeEvents(event); } );
}



void AccelerationComponent::HandleAccelerationChangeEvents(Event *event)
{
	ChangeAccelerationEvent *changeEvent = dynamic_cast<ChangeAccelerationEvent *>(event);
	SDL_assert(changeEvent != nullptr);

	double xVelocity = 0;
	double yVelocity = 0;
	double turnSpeed = 0;

	GetXYVelocity(changeEvent, xVelocity, yVelocity);
	GetTurnSpeed(changeEvent, turnSpeed);

	if (turnSpeed != 0 || xVelocity !=0 || yVelocity != 0)
	{
		GetEventHandler().AddEvent(std::unique_ptr<ChangeVelocityEvent>(new ChangeVelocityEvent(xVelocity, yVelocity, turnSpeed)));
	}
}

void AccelerationComponent::GetXYVelocity(ChangeAccelerationEvent *changeEvent, double &xVelocity, double &yVelocity)
{
	switch (changeEvent->GetDirection())
	{
	case Direction::Up:
		yVelocity = -mMaxAcceleration;
		break;

	case Direction::TopRight:
		xVelocity = sqrt(mMaxAcceleration);
		yVelocity = -sqrt(mMaxAcceleration);
		break;
	case Direction::Right:
		xVelocity = mMaxAcceleration;
		break;

	case Direction::BottomRight:
		xVelocity = sqrt(mMaxAcceleration);
		yVelocity = sqrt(mMaxAcceleration);
		break;

	case Direction::Bottom:
		yVelocity = mMaxAcceleration;
		break;

	case Direction::BottomLeft:
		xVelocity = -sqrt(mMaxAcceleration);
		yVelocity = sqrt(mMaxAcceleration);
		break;

	case Direction::Left:
		xVelocity  =-mMaxAcceleration;
		yVelocity = 0;
		break;
	case Direction::TopLeft:
		xVelocity = -sqrt(mMaxAcceleration);
		yVelocity = -sqrt(mMaxAcceleration);
		break;
    default:
		break;
	}
}


void AccelerationComponent::GetTurnSpeed(ChangeAccelerationEvent *changeEvent, double &turnSpeed)
{

	switch (changeEvent->GetTurnDirection())
	{

	case Direction::Right:
		turnSpeed = mMaxRotationAcceleration;
		break;

	case Direction::Left:
		turnSpeed = -mMaxRotationAcceleration;
		break;
	default:
		break;
	}
}