#include "Event/EventFactory.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/QueryDirectionEvent.h"
#include "Event/ChangeAnimationStateEvent.h"


namespace EventFactory
{
	std::unique_ptr<Event> CreateChangeVelocityEvent(int xVelocityChange, int yVelocityChange, int rotationVelocityChange)
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
}