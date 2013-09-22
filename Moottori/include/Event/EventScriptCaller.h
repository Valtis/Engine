#pragma once
#include "EventVisitor.h"

class EventScriptCaller : public EventVisitor
{
	virtual void visit(const BoundaryCollisionEvent *event) const override;
	virtual void visit(const ChangeAccelerationEvent *event) const override;
	virtual void visit(const ChangeAnimationStateEvent *event) const override;
	virtual void visit(const ChangeLocationEvent *event) const override;
	virtual void visit(const QueryDirectionEvent *event) const override;
	virtual void visit(const RequestTerminationEvent *event) const override;
};