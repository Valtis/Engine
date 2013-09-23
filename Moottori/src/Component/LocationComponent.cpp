#include "Component/LocationComponent.h"
#include <SDL_assert.h>
#include <cmath>

void LocationComponent::OnAttachingScript()
{
	luabind::module(mLuaState.State()) [
		luabind::class_<LocationComponent>("LocationComponent")
			.def_readwrite("x", &LocationComponent::mX)
			.def_readwrite("y", &LocationComponent::mY)
			.def_readwrite("rotation", &LocationComponent::mRotation)
	];

	luabind::globals(mLuaState.State())["location_component"] = this;
}