#pragma once

#include "Utility/Enumerations.h"
#include "EventVisitor.h"
#include <stdexcept>

enum class EventType : int { None, UIEvent, QueryLocation, QueryDirection, QueryFaction, ChangeAcceleration, 
	ChangeVelocity, ChangeLocation, ChangeAnimationState, RequestTermination, BoundaryCollision, EntityCollision,
	SpawnEntity, ParentIDNotification, PlaySoundEffect
};


class Event
{
    public:
        Event();
        virtual ~Event();
        virtual EventType GetType() const = 0;

		virtual void AcceptVisitor(EventVisitor *visitor) const { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	Event(const Event &) = delete;
	Event &operator=(const Event &) = delete;
#else
private:
	Event(const Event &);
	Event &operator=(const Event &);
public:
#endif

    protected:
    private:
};
