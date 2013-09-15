#pragma once

#include "Component.h"
class ChangeVelocityEvent;
class VelocityComponent : public Component
{
public:
	VelocityComponent(int maxVelocity, double turnSpeed);
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

protected:
	void OnEventHandlerRegistration() override;
private:
	void HandleVelocityChangeEvents(Event *event);
	void GetXYVelocity(ChangeVelocityEvent *changeEvent, int &xVelocity, int &yVelocity);
	void GetTurnSpeed(ChangeVelocityEvent *changeEvent, double &turnSpeed);

	int mVelocity;
	double mTurnSpeed;
};