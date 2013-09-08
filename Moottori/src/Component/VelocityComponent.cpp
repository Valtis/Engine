#include "Component/VelocityComponent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeLocationEvent.h"

#include <SDL_assert.h>
#include <cmath>
VelocityComponent::VelocityComponent(int maxVelocity) : mVelocity(maxVelocity)
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

	switch (changeEvent->GetDirection())
	{
	case Direction::Up:
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(0, -mVelocity)));
		break;

	case Direction::TopRight:
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(sqrt(mVelocity), -sqrt(mVelocity))));
		break;
	case Direction::Right:
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(mVelocity, 0)));
		break;

	case Direction::BottomRight:
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(sqrt(mVelocity), sqrt(mVelocity))));
		break;

	case Direction::Bottom:
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(0, mVelocity)));
		break;

	case Direction::BottomLeft:
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(-sqrt(mVelocity), sqrt(mVelocity))));
		break;

	case Direction::Left:
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(-mVelocity, 0)));
		break;
	case Direction::TopLeft:
		GetEventHandler().AddEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(-sqrt(mVelocity), -sqrt(mVelocity))));
		break;

	}

}