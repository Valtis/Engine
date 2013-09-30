#pragma once
#include "Event/Event.h"

#include "Utility/Enumerations.h"
#include "Utility/LuaState.h"


enum class ComponentType : int { None, Input, Acceleration, Velocity, Location, Graphics, Collision, Hitpoints, Faction, Health, SoundEffect };

class EventHandler;
class EventSender;
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

	virtual void OnRegisteringEventHandler(EventHandler *handler)
	{

	}
	LuaState mLuaState;
	
private:
	EventHandler *mEventHandler;
	void HandleEvent(Event *event);
	void RegisterForEvents(EventType type);
	std::unique_ptr<EventSender> mEventSender;

	void AddEmitter(int x, int y, int numberOfParticles, double lifeTime, double maxVelocity); // MOVE TO RIGHT CLASS!! THIS REALLY SHOULDN'T BE HERE!
};