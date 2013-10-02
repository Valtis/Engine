#include "Event/EventActionExecutor.h"
#include "Event/BoundaryCollisionEvent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeAnimationStateEvent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/QueryDirectionEvent.h"
#include "Event/RequestTerminationEvent.h"
#include "Event/EntityCollisionEvent.h"
#include "Event/ParentIDNotificationEvent.h"

void EventActionExecutor::Visit(const BoundaryCollisionEvent *event) const
{
	mState.CallFunction("OnBoundaryCollisionEvent", static_cast<int>(event->GetCollisionDirection()), event->GetMinX(), event->GetMinY(), event->GetMaxX(), event->GetMaxY());
}


void EventActionExecutor::Visit(const ChangeAccelerationEvent *event) const 
{
	mState.CallFunction("OnAccelerationChangeEvent", static_cast<int>(event->GetDirection()), static_cast<int>(event->GetTurnDirection()), static_cast<int>(event->GetState()));
}

void EventActionExecutor::Visit(const ChangeVelocityEvent *event) const 
{
	mState.CallFunction("OnVelocityChangeEvent", event->GetXVelocityChange(), event->GetYVelocityChange(), event->GetRotationChange());
}

void EventActionExecutor::Visit(const ChangeLocationEvent *event) const 
{
	mState.CallFunction("OnLocationChangeEvent", event->GetXChange(), event->GetYChange(), event->GetRotationChange());
}

void EventActionExecutor::Visit(const ChangeAnimationStateEvent *event) const 
{
	mState.CallFunction("OnAnimationStateChangeEvent", event->GetAnimationID(), event->GetNewAnimationState());
}


void EventActionExecutor::Visit(const RequestTerminationEvent *event) const 
{
	mState.CallFunction("OnTerminationRequestEvent", event->GetID());	
}

void EventActionExecutor::Visit(const EntityCollisionEvent *event) const
{
	mState.CallFunction("OnEntityCollisionEvent", event->GetFirstEntityID(), event->GetSecondEntityID());
}

void EventActionExecutor::Visit(const ParentIDNotificationEvent *event) const
{
	mState.CallFunction("OnParentIdNotificationEvent", event->GetParentID());
}