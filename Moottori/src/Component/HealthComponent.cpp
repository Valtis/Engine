#include "Component/HealthComponent.h"



void HealthComponent::OnAttachingScript()
{
	luabind::module(mLuaState.State()) [
		luabind::class_<HealthComponent>("HealthComponent")
			.def_readwrite("current_health", &HealthComponent::mCurrentHealth)
			.def_readwrite("max_health", &HealthComponent::mMaxHealth)
	];


	luabind::globals(mLuaState.State())["¨health_component"] = this;
}
