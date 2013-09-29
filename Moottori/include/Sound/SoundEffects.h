#pragma once
#include <SDL_mixer.h>
#include <unordered_map>

#include "Utility/UniqueID.h"
class SoundEffects
{
public:
	SoundEffects();
	virtual ~SoundEffects();
#if !defined _MSC_VER || _MSC_VER >= 1800 
	SoundEffects(const SoundEffects &) = delete;
	SoundEffects &operator=(const SoundEffects &) = delete;
#else
private:
	SoundEffects(const SoundEffects &);
	SoundEffects &operator=(const SoundEffects &);
public:
#endif
	void Initialize();
	void ParseLine( std::string &line );
	void Uninitialize();
	void Play(int id);

protected:
private:

	void LoadEffect( std::string name, int id );
	std::unordered_map<int, Mix_Chunk *> mEffects;

};
