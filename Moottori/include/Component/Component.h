#pragma once

#include "Event/IEventHandler.h"

class Component
{
public:
	Component();

#if (_MSC_VER >= 1800)
	Component(const Component &) = delete;
	Component &operator=(const Component &) = delete;
#else
private:
	Component(const Component &);
	Component &operator=(const Component &);
public:
#endif

	virtual ~Component();


	void RegisterEventHandler(IEventHandler *handler)
	{
		mEventHandler = handler;
		OnEventHandlerRegistration();
	}

	virtual void Update(double ticksPassed)
	{

	}

protected:
	IEventHandler &GetEventHandler() { return *mEventHandler; }
	virtual void OnEventHandlerRegistration()
	{

	}
private:
	IEventHandler *mEventHandler;


};