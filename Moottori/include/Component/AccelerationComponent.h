#pragma once
#include "Component.h"
class ChangeAccelerationEvent;
class AccelerationComponent : public Component
{
public:
	AccelerationComponent(double maxAcceleration, double maxRotationAcceleration) : mCurrentXAcceleration(0), mCurrentYAcceleration(0), mCurrentRotationAcceleration(0),
		mMaxAcceleration(maxAcceleration), mMaxRotationAcceleration(maxRotationAcceleration)  {} 
#if !defined _MSC_VER || _MSC_VER >= 1800 
	AccelerationComponent(const AccelerationComponent &) = delete;
	AccelerationComponent &operator=(const AccelerationComponent &) = delete;
#else
private:
	AccelerationComponent(const AccelerationComponent &);
	AccelerationComponent &operator=(const AccelerationComponent &);
public:
#endif

	void Update(double gameTicksPassed) override;
protected:
	void OnEventHandlerRegistration() override;

private:
	void HandleAccelerationChangeEvents(Event *event);
	void GetXYVelocity(ChangeAccelerationEvent *changeEvent);
	void GetTurnSpeed(ChangeAccelerationEvent *changeEvent);

	double mCurrentXAcceleration;
	double mCurrentYAcceleration;
	double mCurrentRotationAcceleration;

	double mMaxAcceleration;
	double mMaxRotationAcceleration;


};