#pragma once
class IEventHandler;
class LuaState;
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

	void Init(IEventHandler *handler, LuaState *luaState);

private:
	IEventHandler *mEventHandler;
	LuaState *mLuaState;
	void RegisterFunctions();

	void SendDirectionQueryMessage();
	void SendVelocityChangeMessage(double xVelocityChange, double yVelocityChange, double rotationVelocityChange);



};