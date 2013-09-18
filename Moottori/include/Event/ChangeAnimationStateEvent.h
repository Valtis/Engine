#pragma once
#include "Event.h"
class ChangeAnimationStateEvent : public Event
{
public:
	ChangeAnimationStateEvent(bool state) : mNewState(state) { } 

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

private:
	const bool mNewState;

};