#pragma once
#include "EventVisitor.h"
#include "Utility/LuaState.h"

class EventActionExecutor : public EventVisitor
{
public:
	EventActionExecutor(LuaState &state) : mState(state) { }
	~EventActionExecutor() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	EventActionExecutor(const EventActionExecutor &) = delete;
	EventActionExecutor &operator=(const EventActionExecutor &) = delete;
#else
private:
	EventActionExecutor(const EventActionExecutor &);
	EventActionExecutor &operator=(const EventActionExecutor &);
public:
#endif


	virtual void Visit(const BoundaryCollisionEvent *event) const override;
	virtual void Visit(const ChangeAccelerationEvent *event) const override;
	virtual void Visit(const ChangeVelocityEvent *event) const override;
	virtual void Visit(const ChangeLocationEvent *event) const override;
	virtual void Visit(const ChangeAnimationStateEvent *event) const override;
	virtual void Visit(const RequestTerminationEvent *event) const override;
	virtual void Visit(const EntityCollisionEvent *event) const override;
	virtual void Visit(const ParentIDNotificationEvent *event) const override;

	//virtual void Visit(const SpawnParticleEmitterEvent *event) const override;

private:
	LuaState &mState;
};