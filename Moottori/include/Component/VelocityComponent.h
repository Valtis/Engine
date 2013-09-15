#pragma once

#include "Component.h"

class VelocityComponent : public Component
{
public:
	VelocityComponent(double maxVelocity, double maxRotationSpeed, double velocityLossPerTick, double rotationVelocityLossPerTick);
	~VelocityComponent();

#if !defined _MSC_VER || _MSC_VER >= 1800 
	VelocityComponent(const VelocityComponent &) = delete;
	VelocityComponent &operator=(const VelocityComponent &) = delete;
#else
private:
	VelocityComponent(const VelocityComponent &);
	VelocityComponent &operator=(const VelocityComponent &);
public:
#endif

void Update(double ticksPassed) override;

protected:
	void OnEventHandlerRegistration() override;
private:
	void HandleVelocityChangeEvents(Event *event);
	void DecaySpeed();

	double mCurrentXVelocity;
	double mCurrentYVelocity;
	double mCurrentRotationSpeed;
	
	double mVelocityLossPerTick;
	double mRotationVelocityLossPerTick;

	double mMaxVelocity;
	double mMaxRotationSpeed;
};