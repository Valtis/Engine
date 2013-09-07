#pragma once

#include "Enumerations.h"

class Event
{
    public:
        Event();
        virtual ~Event();

        virtual EventType GetType() = 0;

    protected:
    private:
};
