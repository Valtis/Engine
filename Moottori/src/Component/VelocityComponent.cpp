#include "Component/VelocityComponent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/ChangeAnimationStateEvent.h"

#include <SDL_assert.h>
#include <cmath>

#define SIGNUM(x) (((x) < 0) ? -1 : ((x) > 0))

VelocityComponent::VelocityComponent() 
	: mCurrentXVelocity(0), mCurrentYVelocity(0), mCurrentRotationSpeed(0)
{

}

VelocityComponent::~VelocityComponent()
{

}



void VelocityComponent::SendAnimationStateMessage(int animationID, bool animationState)
{
	GetEventHandler().AddEvent(
		std::unique_ptr<ChangeAnimationStateEvent>(
		new ChangeAnimationStateEvent(animationID, animationState)));
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
			.def("SendAnimationStateMessage", &VelocityComponent::SendAnimationStateMessage)
			.def_readwrite("x_velocity", &VelocityComponent::mCurrentXVelocity)
			.def_readwrite("y_velocity", &VelocityComponent::mCurrentYVelocity)
			.def_readwrite("rotation_velocity", &VelocityComponent::mCurrentRotationSpeed)
	];

	luabind::globals(mLuaState.State())["velocity_component"] = this;
}