#pragma once
#include <memory>
#include "Utility/Enumerations.h"
#include "Event/Event.h"

namespace EventFactory
{
	std::unique_ptr<Event> CreateChangeVelocityEvent(double xVelocityChange, double yVelocityChange, double rotationVelocityChange);
	std::unique_ptr<Event> CreateDirectionQueryEvent(double &rotation, bool &wasHandled);
	std::unique_ptr<Event> CreateFactionQueryEvent(int &faction, bool &wasHandled);
	std::unique_ptr<Event> CreateAnimationStateChangeEvent(int animationID, bool animationState);
	std::unique_ptr<Event> CreateChangeAccelerationEvent(Direction accelerationDirection, Direction rotationDirection, UIEventState state);
	std::unique_ptr<Event> CreateChangeLocationEvent(double xPositionChange, double yPositionChange, double rotationChange);
	std::unique_ptr<Event> CreateBoundaryCollisionEvent(Direction direction, int minX, int minY, int maxX, int maxY);
	std::unique_ptr<Event> CreateUIEvent(UIEventType eventType, UIEventState eventState);
	std::unique_ptr<Event> CreateEntityCollisionEvent(int firstID, int secondID);
	std::unique_ptr<Event> CreateEntityTerminationRequestEvent(int id);
	
}