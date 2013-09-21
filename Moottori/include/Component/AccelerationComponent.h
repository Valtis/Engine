#pragma once
#include "Component.h"
class ChangeAccelerationEvent;
class AccelerationComponent : public Component
{
public:
	AccelerationComponent() : mCurrentXAcceleration(0), mCurrentYAcceleration(0), mCurrentRotationAcceleration(0) {} 
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
	void OnAttachingScript() override;

private:
	void SendDirectionQueryMessage();
	void SendAccelerationChangeMessage(double ticksPassed);
	void HandleAccelerationChangeEvents(Event *event);

	double mCurrentXAcceleration;
	double mCurrentYAcceleration;
	double mCurrentRotationAcceleration;

};