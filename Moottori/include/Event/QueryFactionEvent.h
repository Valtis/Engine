#pragma once
#include "Event.h"


class QueryFactionEvent : public Event
{
public:

	QueryFactionEvent(int &faction, bool &wasHandled) : mFaction(faction), mWasHandled(wasHandled) {}

	bool WasHandled() { return mWasHandled; }
	void WasHandled(bool val) { mWasHandled = val; }

	double GetFaction() { return mFaction; }
	void SetFaction(int val) { mFaction= val; }

	EventType GetType() const { return EventType::QueryFaction; }
	
#if !defined _MSC_VER || _MSC_VER >= 1800 
	QueryFactionEvent(const QueryFactionEvent &) = delete;
	QueryFactionEvent &operator=(const QueryFactionEvent &) = delete;
#else
private:
	QueryFactionEvent(const QueryFactionEvent &);
	QueryFactionEvent &operator=(const QueryFactionEvent &);
public:
#endif


private:

	bool &mWasHandled;
	int &mFaction;
};
