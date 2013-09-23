#include "Event/EventSender.h"
#include "Event/IEventHandler.h"
#include "Event/EventFactory.h"
#include "Utility/LuaState.h"


void EventSender::Init(IEventHandler *handler, LuaState *luaState)
{
	mEventHandler = handler;
	mLuaState = luaState;
	RegisterFunctions();
}

void EventSender::RegisterFunctions()
{
	luabind::module(mLuaState->State()) [
		luabind::class_<EventSender>("EventSender")
			.def("SendDirectionQueryMessage", &EventSender::SendDirectionQueryMessage)
			.def("SendVelocityChangeMessage", &EventSender::SendVelocityChangeMessage)
			.def("SendAnimationStateMessage", &EventSender::SendAnimationStateMessage)
			.def("SendAccelerationChangeMessage", &EventSender::SendAccelerationChangeMessage)
			.def("SendLocationChangeMessage", &EventSender::SendLocationChangeMessage)

	];

	luabind::globals(mLuaState->State())["messaging"] = this;	
}

void EventSender::SendDirectionQueryMessage()
{
	double rotation = 0;
	bool wasHandled = false;
	mEventHandler->ProcessEvent(EventFactory::CreateDirectionQueryEvent(rotation, wasHandled));
	
	lua_pushnumber(mLuaState->State(), rotation);
	lua_pushinteger(mLuaState->State(), wasHandled);
	lua_pushinteger(mLuaState->State(), 2); // number of parameters into stack
}

void EventSender::SendVelocityChangeMessage(double xVelocityChange, double yVelocityChange, double rotationVelocityChange)
{
	mEventHandler->ProcessEvent(EventFactory::CreateChangeVelocityEvent(xVelocityChange, yVelocityChange, rotationVelocityChange));
}


void EventSender::SendAnimationStateMessage(int animationID, bool animationState)
{
	mEventHandler->AddEvent(EventFactory::CreateAnimationStateChangeEvent(animationID, animationState));
}


void EventSender::SendAccelerationChangeMessage(Direction accelerationDirection, Direction rotationDirection, UIEventState eventState)
{
	mEventHandler->ProcessEvent(EventFactory::CreateChangeAccelerationEvent(accelerationDirection, rotationDirection, eventState));
}


void EventSender::SendLocationChangeMessage(double xPositionChange, double yPositionChange, double rotationChange)
{
	mEventHandler->ProcessEvent(EventFactory::CreateChangeLocationEvent(xPositionChange, yPositionChange, rotationChange));
}