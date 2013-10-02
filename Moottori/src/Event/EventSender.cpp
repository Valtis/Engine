#include "Event/EventSender.h"
#include "Event/EventHandler.h"
#include "Event/EventFactory.h"
#include "Utility/LuaState.h"
#include "Utility/LoggerManager.h"
#include "Entity/Entity.h"
#include "Entity/EntityManager.h"

EventSender::EventSender() : mEventHandler(new EventHandlerHelper())
{
	
}

void EventSender::Initialize(EventHandler *handler)
{
	mEventHandler->mEventHandler = handler;

}

void EventSender::RegisterFunctions(LuaState *state)
{
	mLuaState = state;
	luabind::module(mLuaState->State()) [
		luabind::class_<EventSender>("EventSender")
			.def("SendDirectionQueryMessage", &EventSender::SendDirectionQueryMessage)
			.def("SendDirectionQueryMessageToEntity", &EventSender::SendDirectionQueryMessageToEntity)
			.def("SendVelocityChangeMessage", &EventSender::SendVelocityChangeMessage)
			.def("SendAnimationStateMessage", &EventSender::SendAnimationStateMessage)
			.def("SendAccelerationChangeMessage", &EventSender::SendAccelerationChangeMessage)
			.def("SendLocationChangeMessage", &EventSender::SendLocationChangeMessage)
			.def("SendEntityTerminationRequestMessage", &EventSender::SendEntityTerminationRequestMessage)
			.def("SendFactionQueryMessage", &EventSender::SendFactionQueryMessage)
			.def("SendFactionQueryMessageToEntity", &EventSender::SendFactionQueryMessageToEntity)
			.def("SendLocationQueryMessage", &EventSender::SendLocationQueryMessage)
			.def("SendLocationQueryMessageToEntity", &EventSender::SendLocationQueryMessageToEntity)
	];

	luabind::globals(mLuaState->State())["messaging"] = this;	
}

void EventSender::SendDirectionQueryMessage()
{
	HandleDirectionQueryMessage(mEventHandler->mEventHandler);
}


void EventSender::SendDirectionQueryMessageToEntity( int id )
{
	Entity *e = EntityManager::Instance().GetEntity(id);
	if (e == nullptr)
	{
		LoggerManager::GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning,
			"Could not find entity with id " + std::to_string(id) + " when querying for direction data"
			);
	}
	HandleDirectionQueryMessage(e);
}


void EventSender::HandleDirectionQueryMessage( EventHandler *handler )
{
	double rotation = 0;
	bool wasHandled = false;
	if (handler != nullptr)
	{
		handler->ProcessEvent(EventFactory::CreateDirectionQueryEvent(rotation, wasHandled));
	}

	lua_pushnumber(mLuaState->State(), rotation);
	lua_pushinteger(mLuaState->State(), wasHandled);
	lua_pushinteger(mLuaState->State(), 2); // number of parameters into stack
}



void EventSender::SendLocationQueryMessage()
{
	HandleLocationQueryMessage(mEventHandler->mEventHandler);
}



void EventSender::SendLocationQueryMessageToEntity( int id )
{
	Entity *e = EntityManager::Instance().GetEntity(id);
	if (e == nullptr)
	{
		LoggerManager::GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning,
			"Could not find entity with id " + std::to_string(id) + " when querying for location data"
			);
	}
	HandleLocationQueryMessage(e);
}

void EventSender::HandleLocationQueryMessage( EventHandler *handler )
{
	double x = 0;
	double y = 0;
	bool wasHandled = false;
	if (handler != nullptr)
	{
		handler->ProcessEvent(EventFactory::CreateLocationQueryEvent(x, y, wasHandled));
	}

	lua_pushnumber(mLuaState->State(), x);
	lua_pushnumber(mLuaState->State(), y);
	lua_pushinteger(mLuaState->State(), wasHandled);
	lua_pushinteger(mLuaState->State(), 3); // number of parameters into stack
}




void EventSender::SendFactionQueryMessageToEntity(int id)
{
	Entity *e = EntityManager::Instance().GetEntity(id);
	if (e == nullptr)
	{
		LoggerManager::GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning,
			"Could not find entity with id " + std::to_string(id) + " when querying for faction data"
			);
	}
	HandleFactionQueryMessage(e);
}

void EventSender::SendFactionQueryMessage()
{
	
	HandleFactionQueryMessage(mEventHandler->mEventHandler);
}

void EventSender::HandleFactionQueryMessage(EventHandler *handler)
{
	int faction = 0;
	bool wasHandled = false;
	if (handler != nullptr)
	{
		handler->ProcessEvent(EventFactory::CreateFactionQueryEvent(faction, wasHandled));
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
	mEventHandler->ProcessEvent(EventFactory::CreateAnimationStateChangeEvent(animationID, animationState));
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

