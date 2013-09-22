#include "Event/EventScriptCaller.h"
#include "Event/BoundaryCollisionEvent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/ChangeAnimationStateEvent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/QueryDirectionEvent.h"
#include "Event/RequestTerminationEvent.h"

void EventScriptCaller::Visit(const BoundaryCollisionEvent *event) const
{
	mState.CallFunction("OnBoundaryCollisionEvent", event->GetMinX(), event->GetMinY(), event->GetMaxX(), event->GetMaxY());
}


void EventScriptCaller::Visit(const ChangeAccelerationEvent *event) const 
{
	mState.CallFunction("OnAccelerationChangeEvent", static_cast<int>(event->GetDirection()), static_cast<int>(event->GetTurnDirection()), static_cast<int>(event->GetState()));
}

void EventScriptCaller::Visit(const ChangeAnimationStateEvent *event) const 
{
	mState.CallFunction("OnAnimationStateChangeEvent", event->GetAnimationID(), event->GetNewAnimationState());
}

void EventScriptCaller::Visit(const ChangeLocationEvent *event) const 
{
	mState.CallFunction("OnLocationChangeEvent", event->GetXChange(), event->GetYChange(), event->GetRotationChange());
}

void EventScriptCaller::Visit(const QueryDirectionEvent *event) const 
{
	mState.CallFunction("OnDirectionQuery");	
}

void EventScriptCaller::Visit(const RequestTerminationEvent *event) const 
{
	mState.CallFunction("OnTerminationRequestEvent", event->GetID());	
}




//;