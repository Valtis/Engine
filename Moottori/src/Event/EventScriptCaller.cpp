#include "Event/EventScriptCaller.h"
#include "Event/BoundaryCollisionEvent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeAnimationStateEvent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/QueryDirectionEvent.h"
#include "Event/RequestTerminationEvent.h"
#include "Event/EntityCollisionEvent.h"


#include "Event/QueryLocationEvent.h"
#include "Event/QueryDirectionEvent.h"
#include "Event/QueryFactionEvent.h"


void EventScriptCaller::Visit(const BoundaryCollisionEvent *event) const
{
	mState.CallFunction("OnBoundaryCollisionEvent", static_cast<int>(event->GetCollisionDirection()), event->GetMinX(), event->GetMinY(), event->GetMaxX(), event->GetMaxY());
}


void EventScriptCaller::Visit(const ChangeAccelerationEvent *event) const 
{
	mState.CallFunction("OnAccelerationChangeEvent", static_cast<int>(event->GetDirection()), static_cast<int>(event->GetTurnDirection()), static_cast<int>(event->GetState()));
}

void EventScriptCaller::Visit(const ChangeVelocityEvent *event) const 
{
	mState.CallFunction("OnVelocityChangeEvent", event->GetXVelocityChange(), event->GetYVelocityChange(), event->GetRotationChange());
}

void EventScriptCaller::Visit(const ChangeLocationEvent *event) const 
{
	mState.CallFunction("OnLocationChangeEvent", event->GetXChange(), event->GetYChange(), event->GetRotationChange());
}

void EventScriptCaller::Visit(const ChangeAnimationStateEvent *event) const 
{
	mState.CallFunction("OnAnimationStateChangeEvent", event->GetAnimationID(), event->GetNewAnimationState());
}

void EventScriptCaller::Visit(const QueryLocationEvent *event, double &x, double &y) const 
{
	mState.CallFunction("OnLocationQuery");	
}

void EventScriptCaller::Visit(const QueryDirectionEvent *event, double &rotation) const 
{
	rotation = mState.CallFunction<double>("OnDirectionQuery");	
}

void EventScriptCaller::Visit(const QueryFactionEvent *event, int &faction) const 
{
	faction= mState.CallFunction<int>("OnFactionQuery");	
}


void EventScriptCaller::Visit(const RequestTerminationEvent *event) const 
{
	mState.CallFunction("OnTerminationRequestEvent", event->GetID());	
}

void EventScriptCaller::Visit(const EntityCollisionEvent *event) const
{
	mState.CallFunction("OnEntityCollisionEvent", event->GetFirstEntityID(), event->GetSecondEntityID());
}

