#pragma once
#include "Event.h"

class EntityCollisionEvent : public Event
{
public:
	EntityCollisionEvent(int firstID, int secondID) : mFirstEntityID(firstID), mSecondEntityID(secondID) { }
	~EntityCollisionEvent() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	EntityCollisionEvent(const EntityCollisionEvent &) = delete;
	EntityCollisionEvent &operator=(const EntityCollisionEvent &) = delete;
#else
private:
	EntityCollisionEvent(const EntityCollisionEvent &);
	EntityCollisionEvent &operator=(const EntityCollisionEvent &);
public:
#endif


	void AcceptVisitor(EventVisitor *visitor) const override 
	{
		visitor->Visit(this);
	}

	int GetFirstEntityID() const { return mFirstEntityID; }
	int GetSecondEntityID() const { return mSecondEntityID; }

	EventType GetType() const override { return EventType::EntityCollision; }
private:
	const int mFirstEntityID;
	const int mSecondEntityID;
}; 