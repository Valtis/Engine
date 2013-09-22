#pragma once
#include "Event.h"
class ChangeLocationEvent : public Event
{
public:
	ChangeLocationEvent(double xChange, double yChange) : mXChange(xChange), mYChange(yChange), mRotationChange(0) { }
	ChangeLocationEvent(double xChange, double yChange, double rotationChange) : mXChange(xChange), mYChange(yChange), mRotationChange(rotationChange) { }

	virtual ~ChangeLocationEvent() { }
#if !defined _MSC_VER || _MSC_VER >= 1800 
	ChangeLocationEvent(const ChangeLocationEvent &) = delete;
	ChangeLocationEvent &operator=(const ChangeLocationEvent &) = delete;
#else
private:
	ChangeLocationEvent(const ChangeLocationEvent &);
	ChangeLocationEvent &operator=(const ChangeLocationEvent &);
public:
#endif

	EventType GetType() const override { return EventType::ChangeLocation; }
	double GetXChange() const { return mXChange; }
	double GetYChange() const { return mYChange; }
	double GetRotationChange() const { return mRotationChange; }

	void AcceptVisitor(EventVisitor *visitor) const override 
	{
		visitor->Visit(this);
	}

private:
	const double mXChange;
	const double mYChange;
	const double mRotationChange;
};