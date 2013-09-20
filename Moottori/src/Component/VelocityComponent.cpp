#include "Component/VelocityComponent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/ChangeAnimationStateEvent.h"

#include <SDL_assert.h>
#include <cmath>

#define SIGNUM(x) (((x) < 0) ? -1 : ((x) > 0))

VelocityComponent::VelocityComponent(double maxVelocity, double maxRotationSpeed) 
	: mCurrentXVelocity(0), mCurrentYVelocity(0), mCurrentRotationSpeed(0), mMaxVelocity(maxVelocity), mMaxRotationSpeed(maxRotationSpeed)
{

}

VelocityComponent::~VelocityComponent()
{

}



void VelocityComponent::SendAnimationStateEvent(bool animationState)
{
	GetEventHandler().AddEvent(
		std::unique_ptr<ChangeAnimationStateEvent>(
		new ChangeAnimationStateEvent(animationState)));
}

void VelocityComponent::SendVelocityChangeMessage(double ticksPassed)
{
	GetEventHandler().ProcessEvent(std::unique_ptr<ChangeLocationEvent>(new ChangeLocationEvent(mCurrentXVelocity*ticksPassed, mCurrentYVelocity*ticksPassed, mCurrentRotationSpeed*ticksPassed)));
}

void VelocityComponent::OnAttachingScript()
{
	
	luabind::module(mLuaState.State()) [
		luabind::class_<VelocityComponent>("VelocityComponent")
			.def("SendVelocityChangeMessage", &VelocityComponent::SendVelocityChangeMessage)
			.def("SendAnimationStateEvent", &VelocityComponent::SendAnimationStateEvent)
			.def_readwrite("x_velocity", &VelocityComponent::mCurrentXVelocity)
			.def_readwrite("y_velocity", &VelocityComponent::mCurrentYVelocity)
			.def_readwrite("rotation_velocity", &VelocityComponent::mCurrentRotationSpeed)
	];

	luabind::globals(mLuaState.State())["velocity_component"] = this;


}



void VelocityComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeVelocity, [&](Event *event) { this->HandleVelocityChangeEvents(event); });
}




void VelocityComponent::HandleVelocityChangeEvents(Event *event)
{
	ChangeVelocityEvent *changeEvent = dynamic_cast<ChangeVelocityEvent *>(event);
	SDL_assert(changeEvent != nullptr);

	mCurrentXVelocity += changeEvent->GetXVelocityChange();
	mCurrentYVelocity += changeEvent->GetYVelocityChange();
	mCurrentRotationSpeed += changeEvent->GetRotationChange();

	int xSign = SIGNUM(mCurrentXVelocity);
	int ySign = SIGNUM(mCurrentYVelocity);
	int rotateSign = SIGNUM(mCurrentRotationSpeed);

	if (fabs(mCurrentXVelocity) > mMaxVelocity)
	{
		mCurrentXVelocity = mMaxVelocity*xSign;
	}

	if (fabs(mCurrentYVelocity) > mMaxVelocity)
	{
		mCurrentYVelocity = mMaxVelocity*ySign;
	}

	if (fabs(mCurrentRotationSpeed) > mMaxRotationSpeed)
	{
		mCurrentRotationSpeed = mMaxRotationSpeed*rotateSign;
	}

}