#pragma once
#include "Event.h"

class EntityCollisionEvent : public Event
{
public:
	EntityCollisionEvent(int id) : mEntityThatCollidedID(id) { }
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

	int GetCollidedEntityID() const { return mEntityThatCollidedID; }
	EventType GetType() const override { return EventType::EntityCollision; }
private:
	const int mEntityThatCollidedID;
}; 