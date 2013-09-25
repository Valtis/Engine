#include "Event/EventFactory.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/QueryDirectionEvent.h"
#include "Event/ChangeAnimationStateEvent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/BoundaryCollisionEvent.h"
#include "Event/EntityCollisionEvent.h"
#include "Event/UIEvent.h"

namespace EventFactory
{
	std::unique_ptr<Event> CreateChangeVelocityEvent(double xVelocityChange, double yVelocityChange, double rotationVelocityChange)
	{

		return std::unique_ptr<Event>(new ChangeVelocityEvent(xVelocityChange, 
			yVelocityChange, rotationVelocityChange));

	}

	std::unique_ptr<Event> CreateDirectionQueryEvent(double &rotation, bool &wasHandled)
	{
		return std::unique_ptr<QueryDirectionEvent>(new QueryDirectionEvent(rotation, wasHandled));
	}

	std::unique_ptr<Event> CreateAnimationStateChangeEvent(int animationID, bool animationState)
	{
		return std::unique_ptr<ChangeAnimationStateEvent>(new ChangeAnimationStateEvent(animationID, animationState));
	}

	std::unique_ptr<Event> CreateChangeAccelerationEvent(Direction accelerationDirection, Direction rotationDirection, UIEventState state) 
	{
		return std::unique_ptr<ChangeAccelerationEvent>(new ChangeAccelerationEvent(accelerationDirection, rotationDirection, state));
	}

	std::unique_ptr<Event> CreateChangeLocationEvent(double xPositionChange, double yPositionChange, double rotationChange)
	{
		return std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(xPositionChange,yPositionChange, rotationChange));
	}

	std::unique_ptr<Event> CreateBoundaryCollisionEvent(Direction direction, int minX, int minY, int maxX, int maxY)
	{
		return std::unique_ptr<BoundaryCollisionEvent>(new BoundaryCollisionEvent(direction, minX, minY, maxX, maxY));
	}

	std::unique_ptr<Event> CreateEntityCollisionEvent(int firstID, int secondID)
	{
		return std::unique_ptr<EntityCollisionEvent>(new EntityCollisionEvent(firstID, secondID));
	}

	std::unique_ptr<Event> CreateUIEvent(UIEventType eventType, UIEventState eventState)
	{
		return std::unique_ptr<UIEvent>(new UIEvent(eventType, eventState));
	}



}