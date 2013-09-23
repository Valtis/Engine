#include "Component/AccelerationComponent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/QueryDirectionEvent.h"
#include <cmath>
#include "SDL_assert.h"

void AccelerationComponent::OnAttachingScript()
{

	luabind::module(mLuaState.State()) [
		luabind::class_<AccelerationComponent>("AccelerationComponent")
			.def_readwrite("x_acceleration", &AccelerationComponent::mCurrentXAcceleration)
			.def_readwrite("y_acceleration", &AccelerationComponent::mCurrentYAcceleration)
			.def_readwrite("rotation_acceleration", &AccelerationComponent::mCurrentRotationAcceleration)
	];

	luabind::globals(mLuaState.State())["acceleration_component"] = this;
}

