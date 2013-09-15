#pragma once
#include "Component.h"
class ChangeAccelerationEvent;
class AccelerationComponent : public Component
{
public:
	AccelerationComponent(double maxAcceleration, double maxRotationAcceleration) : mMaxAcceleration(maxAcceleration), mMaxRotationAcceleration(maxRotationAcceleration)  {} 
#if !defined _MSC_VER || _MSC_VER >= 1800 
	AccelerationComponent(const AccelerationComponent &) = delete;
	AccelerationComponent &operator=(const AccelerationComponent &) = delete;
#else
private:
	AccelerationComponent(const AccelerationComponent &);
	AccelerationComponent &operator=(const AccelerationComponent &);
public:
#endif

protected:
	void OnEventHandlerRegistration() override;

private:
	void HandleAccelerationChangeEvents(Event *event);
	void GetXYVelocity(ChangeAccelerationEvent *changeEvent, double &xVelocity, double &yVelocity);
	void GetTurnSpeed(ChangeAccelerationEvent *changeEvent, double &turnSpeed);

	double mMaxAcceleration;
	double mMaxRotationAcceleration;


};