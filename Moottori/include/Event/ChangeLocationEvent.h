#pragma once
#include "Event.h"
class ChangeLocationEvent : public Event
{
public:
	ChangeLocationEvent(int xChange, int yChange) : mXChange(xChange), mYChange(yChange) { }
	virtual ~ChangeLocationEvent() { }
#if (_MSC_VER >= 1800)
	ChangeLocationEvent(const ChangeLocationEvent &) = delete;
	ChangeLocationEvent &operator=(const ChangeLocationEvent &) = delete;
#else
private:
	ChangeLocationEvent(const ChangeLocationEvent &);
	ChangeLocationEvent &operator=(const ChangeLocationEvent &);
public:
#endif

	EventType GetType() const override { return EventType::ChangeLocation; }
	int GetXChange() const { return mXChange; }
	int GetYChange() const { return mYChange; }

private:
	const int mXChange;
	const int mYChange;
};