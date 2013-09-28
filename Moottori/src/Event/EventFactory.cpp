#include "Event/EventFactory.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/QueryLocationEvent.h"
#include "Event/QueryDirectionEvent.h"
#include "Event/QueryFactionEvent.h"
#include "Event/ChangeAnimationStateEvent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/BoundaryCollisionEvent.h"
#include "Event/EntityCollisionEvent.h"
#include "Event/RequestTerminationEvent.h"
#include "Event/SpawnEntityEvent.h"
#include "Event/ParentIDNotificationEvent.h"
#include "Event/UIEvent.h"

namespace EventFactory
{
	std::unique_ptr<Event> CreateChangeVelocityEvent(double xVelocityChange, double yVelocityChange, double rotationVelocityChange)
	{
		return std::unique_ptr<Event>(new ChangeVelocityEvent(xVelocityChange, 
			yVelocityChange, rotationVelocityChange));
	}
	
	std::unique_ptr<Event> CreateLocationQueryEvent(double &x, double &y, bool &wasHandled)
	{
		return std::unique_ptr<Event>(new QueryLocationEvent(x, y, wasHandled));
	}


	std::unique_ptr<Event> CreateDirectionQueryEvent(double &rotation, bool &wasHandled)
	{
		return std::unique_ptr<Event>(new QueryDirectionEvent(rotation, wasHandled));
	}

	std::unique_ptr<Event> CreateFactionQueryEvent(int &faction, bool &wasHandled)
	{
		return std::unique_ptr<Event>(new QueryFactionEvent(faction, wasHandled));
	}

	std::unique_ptr<Event> CreateAnimationStateChangeEvent(int animationID, bool animationState)
	{
		return std::unique_ptr<Event>(new ChangeAnimationStateEvent(animationID, animationState));
	}

	std::unique_ptr<Event> CreateChangeAccelerationEvent(Direction accelerationDirection, Direction rotationDirection, UIEventState state) 
	{
		return std::unique_ptr<Event>(new ChangeAccelerationEvent(accelerationDirection, rotationDirection, state));
	}

	std::unique_ptr<Event> CreateChangeLocationEvent(double xPositionChange, double yPositionChange, double rotationChange)
	{
		return std::unique_ptr<Event>(new ChangeLocationEvent(xPositionChange,yPositionChange, rotationChange));
	}

	std::unique_ptr<Event> CreateBoundaryCollisionEvent(Direction direction, int minX, int minY, int maxX, int maxY)
	{
		return std::unique_ptr<Event>(new BoundaryCollisionEvent(direction, minX, minY, maxX, maxY));
	}

	std::unique_ptr<Event> CreateEntityCollisionEvent(int firstID, int secondID)
	{ø
		return std::unique_ptr<Event>(new EntityCollisionEvent(firstID, secondID));
	}

	std::unique_ptr<Event> CreateUIEvent(int eventType, UIEventState eventState)
	{
		return std::unique_ptr<Event>(new UIEvent(eventType, eventState));
	}

	std::unique_ptr<Event> CreateEntityTerminationRequestEvent(int id)
	{
		return std::unique_ptr<Event>(new RequestTerminationEvent(id));
	}

	std::unique_ptr<Event> CreateSpawnEntityEvent(std::string scriptName, int parentID)
	{
		return std::unique_ptr<Event>(new SpawnEntityEvent(scriptName, parentID));
	}

	std::unique_ptr<Event> CreateParentIDNotificationEvent(int parentID)
	{
		return std::unique_ptr<Event>(new ParentIDNotificationEvent(parentID));
	}
}