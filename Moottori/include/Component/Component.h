#pragma once

#include "Event/Event.h"
#include "Event/IEventHandler.h"

//#include "Event/EventSender.h"
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
		
		if (mLuaState.FunctionExists("OnRegisterForEvents"))
		{
			mLuaState.CallFunction("OnRegisterForEvents");
		}	

	}

	void Update(double ticksPassed);

protected:
	IEventHandler &GetEventHandler() { return *mEventHandler; }




	virtual void OnAttachingScript()
	{
	
	}	
	LuaState mLuaState;

	
private:
		void RegisterForEvents(EventType type);
//	EventSender mEventSender;
	
	void HandleEvent(Event *event);
	IEventHandler *mEventHandler;

};