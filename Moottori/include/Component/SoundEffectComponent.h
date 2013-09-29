#pragma once

#include "Component.h"

class SoundEffectComponent : public Component
{
public:
	SoundEffectComponent() { }
	~SoundEffectComponent() { }
#if !defined _MSC_VER || _MSC_VER >= 1800 
	SoundEffectComponent(const SoundEffectComponent &) = delete;
	SoundEffectComponent &operator=(const SoundEffectComponent &) = delete;
#else
private:
	SoundEffectComponent(const SoundEffectComponent &);
	SoundEffectComponent &operator=(const SoundEffectComponent &);
public:
#endif


protected:
	void OnAttachingScript() override;
private:
	void PlaySoundEffect(int id);

};