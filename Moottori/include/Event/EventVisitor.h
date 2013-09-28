#pragma once

class BoundaryCollisionEvent;
class ChangeAccelerationEvent;
class ChangeAnimationStateEvent;
class ChangeLocationEvent;
class ChangeVelocityEvent;
class RequestTerminationEvent;
class EntityCollisionEvent;

class QueryLocationEvent; 
class QueryDirectionEvent;
class QueryFactionEvent;

class EventVisitor
{
public:
	virtual void Visit(const BoundaryCollisionEvent *event) const = 0;
	virtual void Visit(const ChangeAccelerationEvent *event) const = 0;
	virtual void Visit(const ChangeVelocityEvent *event) const = 0;
	virtual void Visit(const ChangeLocationEvent *event) const = 0;
	virtual void Visit(const ChangeAnimationStateEvent *event) const = 0;
	virtual void Visit(const QueryLocationEvent *event) const = 0;
	virtual void Visit(const QueryDirectionEvent *event, double &rotation) const = 0;
	virtual void Visit(const QueryFactionEvent *event, int &faction) const = 0;
	virtual void Visit(const RequestTerminationEvent *event) const = 0;
	virtual void Visit(const EntityCollisionEvent *event, double &x, double &y) const = 0;
};