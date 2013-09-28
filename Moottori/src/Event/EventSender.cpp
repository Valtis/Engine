#include "Event/EventSender.h"
#include "Event/EventHandler.h"
#include "Event/EventFactory.h"
#include "Utility/LuaState.h"
#include "Utility/LoggerManager.h"
#include "Entity/Entity.h"
#include "Entity/EntityManager.h"

void EventSender::Init(EventHandler *handler, LuaState *luaState)
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
			.def("SendEntityTerminationRequestMessage", &EventSender::SendEntityTerminationRequestMessage)
			.def("SendFactionQueryMessage", &EventSender::SendFactionQueryMessage)
			.def("SendFactionQueryMessageToEntity", &EventSender::SendFactionQueryMessageToEntity)
			.def("SendLocationQueryMessage", &EventSender::SendLocationQueryMessage)
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

void EventSender::SendLocationQueryMessage()
{
	double x = 0;
	double y = 0;
	bool wasHandled = false;
	mEventHandler->ProcessEvent(EventFactory::CreateLocationQueryEvent(x, y, wasHandled));

	lua_pushnumber(mLuaState->State(), x);
	lua_pushnumber(mLuaState->State(), y);
	lua_pushinteger(mLuaState->State(), wasHandled);
	lua_pushinteger(mLuaState->State(), 3); // number of parameters into stack

}

void EventSender::SendFactionQueryMessage()
{
	int faction = 0;
	bool wasHandled = false;
	mEventHandler->ProcessEvent(EventFactory::CreateFactionQueryEvent(faction, wasHandled));

	lua_pushinteger(mLuaState->State(), faction);
	lua_pushinteger(mLuaState->State(), wasHandled);
	lua_pushinteger(mLuaState->State(), 2); // number of parameters into stack
}

void EventSender::SendFactionQueryMessageToEntity(int id)
{
	
	int faction = 0;
	bool wasHandled = false;

	Entity *e = EntityManager::Instance().GetEntity(id);
	if (e != nullptr)
	{

		e->ProcessEvent(EventFactory::CreateFactionQueryEvent(faction, wasHandled));
	}
	else
	{
		LoggerManager::Instance().GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning,
			"Could not find entity with id " + std::to_string(id) + " when querying for faction data"
			);
	}

	lua_pushinteger(mLuaState->State(), faction);
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

void EventSender::SendEntityTerminationRequestMessage(int id)
{
	mEventHandler->ProcessEvent(EventFactory::CreateEntityTerminationRequestEvent(id));
}