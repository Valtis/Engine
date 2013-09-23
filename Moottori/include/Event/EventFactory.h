#pragma once
#include <memory>


class Event;
namespace EventFactory
{
	std::unique_ptr<Event> CreateChangeVelocityEvent(int xVelocityChange, int yVelocityChange, int rotationVelocityChange);
	std::unique_ptr<Event> CreateDirectionQueryEvent(double &rotation, bool &wasHandled);
}