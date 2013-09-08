#pragma once
#include "Event.h"


class UIEvent : public Event
{
public:
	UIEvent(UIEventType type) : mUIEventType(type) { }
	virtual ~UIEvent() { }

	EventType GetType() const override{ return EventType::UIEvent; }
	UIEventType GetUIEventType() const { return mUIEventType; }
private:
	UIEventType mUIEventType;
};