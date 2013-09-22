#pragma once
#include "Event.h"
class ChangeAnimationStateEvent : public Event
{
public:
	ChangeAnimationStateEvent(int animationID, bool state) : mAnimationID(animationID), mNewState(state) { } 

	int GetAnimationID() const { return mAnimationID; }
	bool GetNewAnimationState() const { return mNewState; };
		
	EventType GetType() const override { return EventType::ChangeAnimationState; }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	ChangeAnimationStateEvent(const ChangeAnimationStateEvent &) = delete;
	ChangeAnimationStateEvent &operator=(const ChangeAnimationStateEvent &) = delete;
#else
private:
	ChangeAnimationStateEvent(const ChangeAnimationStateEvent &);
	ChangeAnimationStateEvent &operator=(const ChangeAnimationStateEvent &);
public:
#endif

	void AcceptVisitor(EventVisitor *visitor) const override 
	{
		visitor->Visit(this);
	}

private:
	const int mAnimationID;
	const bool mNewState;

};