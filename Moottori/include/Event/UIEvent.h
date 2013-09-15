#pragma once
#include "Event.h"


class UIEvent : public Event
{
public:
	UIEvent(UIEventType type, UIEventState state) : mUIEventType(type), mUIEventState(state) { }
	virtual ~UIEvent() { }

	EventType GetType() const override{ return EventType::UIEvent; }
	UIEventType GetUIEventType() const { return mUIEventType; }
	UIEventState GetUIEventState() const { return mUIEventState; }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	UIEvent(const UIEvent &) = delete;
	UIEvent &operator=(const UIEvent &) = delete;
#else
private:
	UIEvent(const UIEvent &);
	UIEvent &operator=(const UIEvent &);
public:
#endif

private:
	const UIEventType mUIEventType;
	const UIEventState mUIEventState;
};