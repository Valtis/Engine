#pragma once
#include "Event.h"
class BoundaryCollisionEvent : public Event
{
public:
	BoundaryCollisionEvent(Direction direction, int minX, int minY, int maxX, int maxY) : mCollisionDirection(direction), mMinX(minX), mMinY(minY), mMaxX(maxX), mMaxY(maxY) {}
	~BoundaryCollisionEvent() { }


	EventType GetType() const override { return EventType::BoundaryCollision; }

	Direction GetCollisionDirection() const { return mCollisionDirection; }
	
	int GetMinX() const { return mMinX; }
	int GetMinY() const { return mMinY; }

	int GetMaxX() const { return mMaxX; }
	int GetMaxY() const { return mMaxY; }

private:
	const Direction mCollisionDirection;
	
	const int mMinX;
	const int mMinY; 

	const int mMaxX;
	const int mMaxY;
};

