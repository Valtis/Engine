#pragma once

#include "Event/Event.h"

class PlaySoundEffectEvent : public Event
{
public:
	PlaySoundEffectEvent(int effectID) : mEffectID(effectID) { }
	~PlaySoundEffectEvent() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	PlaySoundEffectEvent(const PlaySoundEffectEvent &) = delete;
	PlaySoundEffectEvent &operator=(const PlaySoundEffectEvent &) = delete;
#else
private:
	PlaySoundEffectEvent(const PlaySoundEffectEvent &);
	PlaySoundEffectEvent &operator=(const PlaySoundEffectEvent &);
public:
#endif

	EventType GetType() const override { return EventType::PlaySoundEffect; }
	int GetEffectID() const { return mEffectID; }


private:
	const int mEffectID;
};



