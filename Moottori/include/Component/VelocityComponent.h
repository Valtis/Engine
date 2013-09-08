#pragma once

#include "Component.h"
class VelocityComponent : public Component
{
public:
	VelocityComponent(int maxVelocity);
	~VelocityComponent();
protected:
	void OnEventHandlerRegistration() override;
private:
	void HandleVelocityChangeEvents(Event *event);

	int mVelocity;
};