#pragma once

#include "Component.h"

class VelocityComponent : public Component
{
public:
	VelocityComponent();
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
	virtual void OnAttachingScript() override;
private:
	double mCurrentXVelocity;
	double mCurrentYVelocity;
	double mCurrentRotationSpeed;
	

	double mMaxVelocity;
	double mMaxRotationSpeed;
};