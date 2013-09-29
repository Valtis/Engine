#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <sstream>
#include <tuple>

#include <SDL.h>
#include <SDL_mixer.h>

class Music;
class SoundEffects;


class SoundManager
{
public:

	virtual ~SoundManager();

	void UninitializeSDLAudio();

	void ShutdownMix();

	void UninitializeMix();

#if !defined _MSC_VER || _MSC_VER >= 1800 
	SoundManager(const SoundManager &) = delete;
	SoundManager &operator=(const SoundManager &) = delete;
#else
private:
	SoundManager(const SoundManager &);
	SoundManager &operator=(const SoundManager &);
public:
#endif

	static void Release();

	static SoundManager &Instance();

	void Play();
	void Pause();
	void Resume();
	void Stop();
	void Next();
	void Previous();
	void Update(double ticks_passed);

private:
	SoundManager(int frequency, int chunckSize);

	void LoadSoundEffects();

	void LoadMusic();

	void InitializeOggSupport();

	void OpenMixAudio( int frequency, int chunkSize );

	void InitializeSDLSoundSubsystem();

	static SoundManager *mInstance;

	std::unique_ptr<Music> mMusic;
	std::unique_ptr<SoundEffects> mSoundEffects;

};
