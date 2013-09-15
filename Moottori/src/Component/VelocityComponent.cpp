#include "Component/VelocityComponent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeLocationEvent.h"

#include <SDL_assert.h>
#include <cmath>
VelocityComponent::VelocityComponent(int maxVelocity, double turnSpeed) : mVelocity(maxVelocity), mTurnSpeed(turnSpeed)
{

}

VelocityComponent::~VelocityComponent()
{

}

void VelocityComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeVelocity, [&](Event *event) { this->HandleVelocityChangeEvents(event); });
}

void VelocityComponent::HandleVelocityChangeEvents(Event *event)
{
	ChangeVelocityEvent *changeEvent = dynamic_cast<ChangeVelocityEvent *>(event);
	SDL_assert(changeEvent != nullptr);
	int xVelocity = 0;
	int yVelocity = 0;
	double turnSpeed = 0;

	GetXYVelocity(changeEvent, xVelocity, yVelocity);
	GetTurnSpeed(changeEvent, turnSpeed);

	if (turnSpeed != 0 || xVelocity !=0 || yVelocity != 0)
	{
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(xVelocity, yVelocity, turnSpeed)));
	}
}

void VelocityComponent::GetXYVelocity(ChangeVelocityEvent *changeEvent, int &xVelocity, int &yVelocity)
{
	switch (changeEvent->GetDirection())
	{
	case Direction::Up:
		yVelocity = -mVelocity;
		break;

	case Direction::TopRight:
		xVelocity = sqrt(mVelocity);
		yVelocity = -sqrt(mVelocity);
		break;
	case Direction::Right:
		xVelocity = mVelocity;
		break;

	case Direction::BottomRight:
		xVelocity = sqrt(mVelocity);
		yVelocity = sqrt(mVelocity);
		break;

	case Direction::Bottom:
		yVelocity = mVelocity;
		break;

	case Direction::BottomLeft:
		xVelocity = -sqrt(mVelocity);
		yVelocity = sqrt(mVelocity);
		break;

	case Direction::Left:
		xVelocity  =-mVelocity;
		yVelocity = 0;
		break;
	case Direction::TopLeft:
		xVelocity = -sqrt(mVelocity);
		yVelocity = -sqrt(mVelocity);
		break;
    default:
		break;
	}
}


void VelocityComponent::GetTurnSpeed(ChangeVelocityEvent *changeEvent, double &turnSpeed)
{

	switch (changeEvent->GetTurnDirection())
	{

	case Direction::Right:
		turnSpeed = mTurnSpeed;
		break;

	case Direction::Left:
		turnSpeed = -mTurnSpeed;
		break;
	default:
		break;
	}
}