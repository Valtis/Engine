#pragma once

#include "Event/Event.h"

class ParentIDNotificationEvent : public Event
{
public:
	ParentIDNotificationEvent(int parentID) : mParentID(parentID) {}
	~ParentIDNotificationEvent() { }

	
	EventType GetType() const override { return EventType::ParentIDNotification; } 

	int GetParentID() const { return mParentID; }

	void AcceptVisitor(EventVisitor *visitor) const override
	{
		visitor->Visit(this);
	}

#if !defined _MSC_VER || _MSC_VER >= 1800 
	ParentIDNotificationEvent(const ParentIDNotificationEvent &) = delete;
	ParentIDNotificationEvent &operator=(const ParentIDNotificationEvent &) = delete;
#else
private:
	ParentIDNotificationEvent(const ParentIDNotificationEvent &);
	ParentIDNotificationEvent &operator=(const ParentIDNotificationEvent &);
public:
#endif


private:
	const int mParentID;
};