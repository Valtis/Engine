#pragma once

#include "Event/Event.h"


class SpawnEntityEvent : public Event
{
public:
	SpawnEntityEvent(std::string entitySpawnScript, int parentID) : mScriptName(entitySpawnScript), mParentID(parentID) { }
	~SpawnEntityEvent() { }


	EventType GetType() const override  { return EventType::SpawnEntity; }

	std::string GetScriptName() const { return mScriptName; }
	int GetParentID() const { return mParentID; }


#if !defined _MSC_VER || _MSC_VER >= 1800 
	SpawnEntityEvent(const SpawnEntityEvent &) = delete;
	SpawnEntityEvent &operator=(const SpawnEntityEvent &) = delete;
#else
private:
	SpawnEntityEvent(const SpawnEntityEvent &);
	SpawnEntityEvent &operator=(const SpawnEntityEvent &);
public:
#endif

private:
	const std::string mScriptName;
	const int mParentID;

};