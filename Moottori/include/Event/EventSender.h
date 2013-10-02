#pragma once
#include <memory>


#include "Event/EventHandler.h"
#include "Utility/Enumerations.h"
#include "Utility/LoggerManager.h"

class Event;
class LuaState;

class EventSender
{
public:
	EventSender();
	~EventSender() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	EventSender(const EventSender &) = delete;
	EventSender &operator=(const EventSender &) = delete;
#else

private:
	EventSender(const EventSender &);
	EventSender &operator=(const EventSender &);
public:
#endif



	void Initialize(EventHandler *handler);
	void RegisterFunctions(LuaState *luaState);

private:

	class EventHandlerHelper
	{
		public:
		EventHandlerHelper() : mEventHandler(nullptr) { }
		EventHandler *mEventHandler;
		void ProcessEvent(std::unique_ptr<Event> event)
		{

			if (mEventHandler == nullptr)
			{
				LoggerManager::GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning,
					"Script attempting to execute entity function without associated event handler"
					);
				return;
			}
			mEventHandler->ProcessEvent(std::move(event));
		
		}
	};

	std::unique_ptr<EventHandlerHelper> mEventHandler;
	
	LuaState *mLuaState;

	void SendDirectionQueryMessage();
	void SendDirectionQueryMessageToEntity(int id);

	void HandleDirectionQueryMessage(EventHandler *handler);


	void SendLocationQueryMessage();
	void SendLocationQueryMessageToEntity(int id);
	void HandleLocationQueryMessage(EventHandler *handler);

	void SendFactionQueryMessage();
	void SendFactionQueryMessageToEntity(int id);
	void HandleFactionQueryMessage(EventHandler *handler);

	void SendVelocityChangeMessage(double xVelocityChange, double yVelocityChange, double rotationVelocityChange);
	void SendAnimationStateMessage(int animationID, bool animationState);
	void SendAccelerationChangeMessage(Direction accelerationDirection, Direction rotationDirection, UIEventState eventState);
	void SendLocationChangeMessage(double xPositionChange, double yPositionChange, double rotationChange);
	void SendEntityTerminationRequestMessage(int id);
	void SendSpawnEntityMessage(const char *scriptName, int id);
	void SendPlaySoundEffectEvent(int id);


};