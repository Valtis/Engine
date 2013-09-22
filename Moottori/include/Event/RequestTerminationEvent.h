#pragma once
#include "Event.h"

class RequestTerminationEvent : public Event
{
public:
	RequestTerminationEvent(int id) : mID(id) {}
	~RequestTerminationEvent() {}

#if !defined _MSC_VER || _MSC_VER >= 1800 
	RequestTerminationEvent(const RequestTerminationEvent &) = delete;
	RequestTerminationEvent &operator=(const RequestTerminationEvent &) = delete;
#else
private:
	RequestTerminationEvent(const RequestTerminationEvent &);
	RequestTerminationEvent &operator=(const RequestTerminationEvent &);
public:
#endif

	int GetID() const { return mID; }
	EventType GetType() const override { return EventType::RequestTermination; }

	void AcceptVisitor(EventVisitor *visitor) const override 
	{
		visitor->Visit(this);
	}

private:
	const int mID;

};
