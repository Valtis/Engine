#include "Event/EventFactory.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/QueryDirectionEvent.h"


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

}