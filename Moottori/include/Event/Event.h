#pragma once

#include "Utility/Enumerations.h"
#include "EventVisitor.h"
#include <stdexcept>
class Event
{
    public:
        Event();
        virtual ~Event();
        virtual EventType GetType() const = 0;

		// potential refactoring: pass instance of EventVisitor that accepts events and the implementation of the visitor will call proper scripts
		virtual void AcceptVisitor(EventVisitor *visitor) const { throw std::logic_error("Attempting to visit abstract base class Event"); }

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
