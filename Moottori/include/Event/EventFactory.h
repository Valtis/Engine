#pragma once
#include <memory>
#include "Utility/Enumerations.h"

class Event;
namespace EventFactory
{
	std::unique_ptr<Event> CreateChangeVelocityEvent(int xVelocityChange, int yVelocityChange, int rotationVelocityChange);
	std::unique_ptr<Event> CreateDirectionQueryEvent(double &rotation, bool &wasHandled);
	std::unique_ptr<Event> CreateAnimationStateChangeEvent(int animationID, bool animationState);
	std::unique_ptr<Event> CreateChangeAccelerationEvent(Direction accelerationDirection, Direction rotationDirection, UIEventState state);
}