#pragma once
#include "EventVisitor.h"
#include "Utility/LuaState.h"
class EventScriptCaller : public EventVisitor
{
public:
	EventScriptCaller(LuaState &state) : mState(state) { }

	virtual void Visit(const BoundaryCollisionEvent *event) const override;
	virtual void Visit(const ChangeAccelerationEvent *event) const override;
	virtual void Visit(const ChangeAnimationStateEvent *event) const override;
	virtual void Visit(const ChangeLocationEvent *event) const override;
	virtual void Visit(const QueryDirectionEvent *event) const override;
	virtual void Visit(const RequestTerminationEvent *event) const override;

private:
	LuaState &mState;
};