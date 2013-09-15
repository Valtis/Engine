#pragma once
#include "Event.h" 

class ChangeVelocityEvent : public Event
{
public:
	ChangeVelocityEvent(Direction direction) : mDirection(direction), mTurnDirection(Direction::None) { }
	ChangeVelocityEvent(Direction direction, Direction turnDirection) : mDirection(direction), mTurnDirection(turnDirection) { }

	virtual ~ChangeVelocityEvent() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
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
	Direction GetTurnDirection() const { return mTurnDirection; } 

private:
	const Direction mDirection;
	const Direction mTurnDirection;
};