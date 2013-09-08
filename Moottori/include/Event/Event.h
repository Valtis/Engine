#pragma once

#include "Utility/Enumerations.h"

class Event
{
    public:
        Event();
        virtual ~Event();

        virtual EventType GetType() const = 0;

    protected:
    private:
};
