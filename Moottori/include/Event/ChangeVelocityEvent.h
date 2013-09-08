#pragma once
#include "Event.h" 

class ChangeVelocityEvent : public Event
{
public:
	ChangeVelocityEvent(Direction direction) : mDirection(direction) { }
	virtual ~ChangeVelocityEvent() { }

#if (_MSC_VER >= 1800)
	ChangeVelocityEvent(const ChangeVelocityEvent &) = delete;
	ChangeVelocityEvent &operator=(const ChangeVelocityEvent &) = delete;
#else
private:
	ChangeVelocityEvent(const ChangeVelocityEvent &);
	ChangeVelocityEvent &operator=(const ChangeVelocityEvent &);
public:
#endif

	EventType GetType() const override { return EventType::ChangeVelocity; }
	Direction GetDirection() const { return mDirection; }

private:
	const Direction mDirection;
};