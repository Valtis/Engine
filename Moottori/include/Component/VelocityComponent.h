#pragma once

#include "Component.h"
class ChangeVelocityEvent;
class VelocityComponent : public Component
{
public:
	VelocityComponent(int maxVelocity, double turnSpeed);
	~VelocityComponent();
protected:
	void OnEventHandlerRegistration() override;
private:
	void HandleVelocityChangeEvents(Event *event);
	void GetXYVelocity(ChangeVelocityEvent *changeEvent, int &xVelocity, int &yVelocity);
	void GetTurnSpeed(ChangeVelocityEvent *changeEvent, double &turnSpeed);

	int mVelocity;
	double mTurnSpeed;
};