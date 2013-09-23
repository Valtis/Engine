#include "Event/EventSender.h"
#include "Event/Event.h"
#include "Utility/LuaState.h"
#include "Event/IEventHandler.h"
#include "Event/EventFactory.h"


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
