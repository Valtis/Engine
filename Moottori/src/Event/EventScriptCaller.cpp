#include "Event/EventScriptCaller.h"

virtual void EventScriptCaller::visit(BoundaryCollisionEvent *event) const
{

}
virtual void EventScriptCaller::visit(ChangeAccelerationEvent *event) const override;
virtual void EventScriptCaller::visit(ChangeAnimationStateEvent *event) const override;
virtual void EventScriptCaller::visit(ChangeLocationEvent *event) const override;
virtual void EventScriptCaller::visit(QueryDirectionEvent *event) const override;
virtual void EventScriptCaller::visit(RequestTerminationEvent *event) const override;*/



	//state.CallFunction("OnBoundaryCollision", mMinX, mMinY, mMaxX, mMaxY);