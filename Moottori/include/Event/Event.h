#pragma once

#include "Utility/Enumerations.h"

class Event
{
    public:
        Event();
        virtual ~Event();
        virtual EventType GetType() const = 0;

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
