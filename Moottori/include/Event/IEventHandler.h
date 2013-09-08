#pragma once

#include <memory>
#include <functional>

#include "Utility/Enumerations.h"
class Event;

class IEventHandler
{
    public:
        virtual ~IEventHandler() {}

        virtual void AddEvent(std::unique_ptr<Event> event) = 0;
        virtual void ProcessEvent(std::unique_ptr<Event> event) = 0;
		virtual void RegisterCallback(EventType type, std::function<void(Event *)> ) = 0;

};
