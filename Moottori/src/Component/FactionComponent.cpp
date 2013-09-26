#include "Component/FactionComponent.h"

FactionComponent::FactionComponent( int faction ) : mFaction(faction)
{

}

void FactionComponent::OnAttachingScript()
{
	luabind::module(mLuaState.State()) [
		luabind::class_<FactionComponent>("FactionComponent")
			.def_readwrite("faction", &FactionComponent::mFaction)
	];

	luabind::globals(mLuaState.State())["faction_component"] = this;
}