#pragma once
#include "Event/Event.h"
#include "Event/EventSender.h"
#include "Utility/Enumerations.h"
#include "Utility/LuaState.h"


enum class ComponentType : int { None, Input, Acceleration, Velocity, Location, Graphics, Collision, Hitpoints, Faction };

class EventHandler;
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

	void RegisterEventHandler(EventHandler *handler);

	void Update(double ticksPassed);

protected:
	virtual void OnAttachingScript()
	{
	
	}	
	LuaState mLuaState;

	
private:
	EventHandler *mEventHandler;
	void HandleEvent(Event *event);
	void RegisterForEvents(EventType type);
	EventSender mEventSender;
};