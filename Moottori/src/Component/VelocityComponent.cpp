#include "Component/VelocityComponent.h"
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

void VelocityComponent::OnAttachingScript()
{	
	luabind::module(mLuaState.State()) [
		luabind::class_<VelocityComponent>("VelocityComponent")
			.def_readwrite("x_velocity", &VelocityComponent::mCurrentXVelocity)
			.def_readwrite("y_velocity", &VelocityComponent::mCurrentYVelocity)
			.def_readwrite("rotation_velocity", &VelocityComponent::mCurrentRotationSpeed)
	];

	luabind::globals(mLuaState.State())["velocity_component"] = this;
}