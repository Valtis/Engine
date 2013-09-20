#pragma once

#include "Component.h"

class VelocityComponent : public Component
{
public:
	VelocityComponent(double maxVelocity, double maxRotationSpeed);
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
	virtual void OnAttachingScript() override;

	void SendVelocityChangeMessage(double ticksPassed);
private:
	void HandleVelocityChangeEvents(Event *event);

	double mCurrentXVelocity;
	double mCurrentYVelocity;
	double mCurrentRotationSpeed;
	

	double mMaxVelocity;
	double mMaxRotationSpeed;
};