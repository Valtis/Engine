#pragma once
#include "EventVisitor.h"
#include "Utility/LuaState.h"

class EventScriptCaller : public EventVisitor
{
public:
	EventScriptCaller(LuaState &state) : mState(state) { }
	~EventScriptCaller() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	EventScriptCaller(const EventScriptCaller &) = delete;
	EventScriptCaller &operator=(const EventScriptCaller &) = delete;
#else
private:
	EventScriptCaller(const EventScriptCaller &);
	EventScriptCaller &operator=(const EventScriptCaller &);
public:
#endif


	virtual void Visit(const BoundaryCollisionEvent *event) const override;
	virtual void Visit(const ChangeAccelerationEvent *event) const override;
	virtual void Visit(const ChangeVelocityEvent *event) const override;
	virtual void Visit(const ChangeLocationEvent *event) const override;
	virtual void Visit(const ChangeAnimationStateEvent *event) const override;
	virtual void Visit(const RequestTerminationEvent *event) const override;
	virtual void Visit(const EntityCollisionEvent *event) const override;

private:
	LuaState &mState;
};