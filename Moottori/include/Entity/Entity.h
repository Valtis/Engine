#pragma once
#include <map>
#include <deque>
#include <vector>

#include <memory>
#include <functional>

#include "Event/EventHandler.h"
#include "Utility/UniqueID.h"
#include "Utility/Enumerations.h"

class Component;
class Event;

class Entity : public EventHandler
{
public:
	Entity();

#if !defined _MSC_VER || _MSC_VER >= 1800 
	Entity(const Entity &) = delete;
	Entity &operator=(const Entity &) = delete;
#else
private:
	Entity(const Entity &);
	Entity &operator=(const Entity &);
public:
#endif

	virtual ~Entity();


	void AddComponent(ComponentType type, std::unique_ptr<Component> c);
	Component *GetComponent(ComponentType type);

	void AddEvent(std::unique_ptr<Event> event) override;
	void ProcessEvent(std::unique_ptr<Event> event) override;
	void RegisterCallback(EventType type, std::function<void(Event *)> ) override;

	void Update(double ticksPassed);

	int GetID() override { return mID.AsInt(); }
	void SetID(int id) { mID = UniqueID(id); }

protected:
private:

	UniqueID mID;

	typedef std::vector<std::function<void(Event *)>> EventVector;
	std::map<ComponentType, std::unique_ptr<Component>> mComponents;
	std::map<EventType, EventVector> mEventCallbacks;
	std::deque<std::unique_ptr<Event>> mEvents;
};

