#pragma once

#include "Event.h"

class QueryLocationEvent : public Event
{
public:
	QueryLocationEvent(double &x, double &y, bool &wasHandled) : mX(x), mY(y), mWasHandled(wasHandled) { }
	~QueryLocationEvent() { } 



	bool WasHandled() const { return mWasHandled; }
	void WasHandled(bool val) { mWasHandled = val; }

	double GetX() const { return mX; }
	void SetX(double x) { mX = x; }

	double GetY() const { return mY; }
	void SetY(double y) { mY = y; }


	EventType GetType() const override { return EventType::QueryLocation; }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	QueryLocationEvent(const QueryLocationEvent &) = delete;
	QueryLocationEvent &operator=(const QueryLocationEvent &) = delete;
#else

private:
	QueryLocationEvent(const QueryLocationEvent &);
	QueryLocationEvent &operator=(const QueryLocationEvent &);
public:
#endif

private:
	double &mX;
	double &mY;
	bool &mWasHandled;
};