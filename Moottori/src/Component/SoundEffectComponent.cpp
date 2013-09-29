#include "Component/SoundEffectComponent.h"
#include "Sound/SoundManager.h"
void SoundEffectComponent::OnAttachingScript()
{
	luabind::module(mLuaState.State()) [
		luabind::class_<SoundEffectComponent>("SoundEffectComponent")
			.def("PlaySoundEffect", &SoundEffectComponent::PlaySoundEffect)
	];


	luabind::globals(mLuaState.State())["sound_component"] = this;
}


void SoundEffectComponent::PlaySoundEffect(int id)
{
	SoundManager::Instance().PlaySoundEffect(id);
}