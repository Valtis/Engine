#pragma once

#include "Event/Event.h"
#include "Event/IEventHandler.h"
#include "Event/EventScriptCaller.h"
#include "Utility/LuaState.h"
#include <memory>


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

	void RegisterEventHandler(IEventHandler *handler)
	{
		mEventHandler = handler;
	}

	virtual void Update(double ticksPassed);

protected:
	IEventHandler &GetEventHandler() { return *mEventHandler; }

	void RegisterForEvents(EventType type)
	{
		mEventHandler->RegisterCallback(type, [&](Event *event) { this->HandleEvent(event); });
	}


	virtual void OnAttachingScript()
	{
	
	}

	
private:

	
	void HandleEvent(Event *event)
	{
		std::unique_ptr<EventScriptCaller> caller(new EventScriptCaller(mLuaState));
		event->AcceptVisitor(caller.get());
	}

	IEventHandler *mEventHandler;
	LuaState mLuaState;


};