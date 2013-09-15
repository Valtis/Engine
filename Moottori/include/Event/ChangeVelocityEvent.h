#pragma once
#include "Event.h" 

class ChangeVelocityEvent : public Event
{
public:
	ChangeVelocityEvent(double xVelocityChange, double yVelocityChange, double rotationVelocityChange) : mXVelocityChange(xVelocityChange), 
		mYVelocityChange(yVelocityChange), mRotationVelocityChange(rotationVelocityChange)	{ }

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
	double GetXVelocityChange() const { return mXVelocityChange; }
	double GetYVelocityChange() const { return mYVelocityChange; }
	double GetRotationChange() const { return mRotationVelocityChange; }

private:
	const double mXVelocityChange;
	const double mYVelocityChange;
	const double mRotationVelocityChange;
};