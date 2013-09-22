#pragma once
#include "Event.h"
#include "IEventHandler.h"
class QueryDirectionEvent : public Event
{
public:
	QueryDirectionEvent(double &direction, bool &wasHandled) : mDirection(direction), mWasHandled(wasHandled) {}

	bool WasHandled() { return mWasHandled; }
	void WasHandled(bool val) { mWasHandled = val; }

	double GetDirection() { return mDirection; }
	void SetDirection(double val) { mDirection = val; }

	EventType GetType() const { return EventType::QueryDirection; }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	QueryDirectionEvent(const QueryDirectionEvent &) = delete;
	QueryDirectionEvent &operator=(const QueryDirectionEvent &) = delete;
#else
private:
	QueryDirectionEvent(const QueryDirectionEvent &);
	QueryDirectionEvent &operator=(const QueryDirectionEvent &);
public:
#endif
	
	void AcceptVisitor(EventVisitor *visitor) const override 
	{
		visitor->Visit(this, mDirection);
		mWasHandled = true;
	}

private:
	double &mDirection;
	bool &mWasHandled;
};