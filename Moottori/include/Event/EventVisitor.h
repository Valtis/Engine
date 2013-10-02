#pragma once

class BoundaryCollisionEvent;
class ChangeAccelerationEvent;
class ChangeAnimationStateEvent;
class ChangeLocationEvent;
class ChangeVelocityEvent;
class RequestTerminationEvent;
class EntityCollisionEvent;
class ParentIDNotificationEvent;

class EventVisitor
{
public:
	virtual void Visit(const BoundaryCollisionEvent *event) const = 0;
	virtual void Visit(const ChangeAccelerationEvent *event) const = 0;
	virtual void Visit(const ChangeVelocityEvent *event) const = 0;
	virtual void Visit(const ChangeLocationEvent *event) const = 0;
	virtual void Visit(const ChangeAnimationStateEvent *event) const = 0;
	virtual void Visit(const RequestTerminationEvent *event) const = 0;
	virtual void Visit(const EntityCollisionEvent *event) const = 0;
	virtual void Visit(const ParentIDNotificationEvent *event) const = 0;
};