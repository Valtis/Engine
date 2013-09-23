#pragma once
#include "Utility/LuaState.h"
#include "Event/EventSender.h"
#include "Utility/Enumerations.h"
#include "Event/IEventHandler.h"
#include "Event/Event.h"
class IEventHandler;
class Event;
class Component
{
public:
	Component();

#if !defined _MSC_VER || _MSC_VER >= 1800 
	Component(const Component &) = delete;
	Component &operator=(const Component &) = delete;
#else
private:
	Component(const Component &);
	Component &operator=(const Component &);
public:
#endif

	virtual ~Component();

	void AttachScript(std::string scriptFile);

	void RegisterEventHandler(IEventHandler *handler);

	void Update(double ticksPassed);

protected:
	IEventHandler &GetEventHandler() { return *mEventHandler; }
	virtual void OnAttachingScript()
	{
	
	}	
	LuaState mLuaState;

	
private:
	IEventHandler *mEventHandler;
	void HandleEvent(Event *event);
	void RegisterForEvents(EventType type);
	EventSender mEventSender;
};