#pragma once
#include "Event.h"
class ChangeAccelerationEvent : public Event
{
public:
	ChangeAccelerationEvent(Direction direction) : mDirection(direction), mTurnDirection(Direction::None) { }
	ChangeAccelerationEvent(Direction direction, Direction turnDirection) : mDirection(direction), mTurnDirection(turnDirection) { }

	virtual ~ChangeAccelerationEvent() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	ChangeAccelerationEvent(const ChangeAccelerationEvent &) = delete;
	ChangeAccelerationEvent &operator=(const ChangeAccelerationEvent &) = delete;
#else
private:
	ChangeAccelerationEvent(const ChangeAccelerationEvent &);
	ChangeAccelerationEvent &operator=(const ChangeAccelerationEvent &);
public:
#endif

	EventType GetType() const override { return EventType::ChangeAcceleration; }
	Direction GetDirection() const { return mDirection; }
	Direction GetTurnDirection() const { return mTurnDirection; } 

private:
	const Direction mDirection;
	const Direction mTurnDirection;
};