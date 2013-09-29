#pragma once
class EventHandler;
class LuaState;

#include "Utility/Enumerations.h"
class EventSender
{
public:
	EventSender() { }
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



	void Init(EventHandler *handler, LuaState *luaState);

private:
	EventHandler *mEventHandler;
	LuaState *mLuaState;
	void RegisterFunctions();

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