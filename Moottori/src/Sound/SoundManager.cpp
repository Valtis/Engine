#include "Sound/SoundManager.h"
#include <stdexcept>
#include "Sound/Music.h"
#include "Sound/SoundEffects.h"

SoundManager *SoundManager::mInstance = nullptr;

SoundManager::SoundManager(int frequency, int chunkSize) : mMusic()
{
	InitializeSDLSoundSubsystem();
	OpenMixAudio(frequency, chunkSize);
	InitializeOggSupport();
	LoadMusic();
	LoadSoundEffects();
}

void SoundManager::InitializeSDLSoundSubsystem()
{
	if (SDL_InitSubSystem(SDL_INIT_AUDIO))
	{
		throw std::runtime_error("Failed to initialize SDL audio subsystem");
	}
}

void SoundManager::OpenMixAudio( int frequency, int chunkSize )
{

	// stereo with default format
	if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, 2, chunkSize))
	{
		throw std::runtime_error(std::string("Failed to open SDL mixer audio - Error: ") + Mix_GetError());
	}
}

void SoundManager::InitializeOggSupport()
{
	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
	{
		throw std::runtime_error(std::string("Failed to initialize ogg support - Error: ") + Mix_GetError());
	}
}


void SoundManager::LoadMusic()
{
	mMusic.reset(new Music());
	mMusic->Initialize();
}


void SoundManager::LoadSoundEffects()
{
	mSoundEffects.reset(new SoundEffects());
	mSoundEffects->Initialize();
}


SoundManager::~SoundManager()
{
	UninitializeMix();
	ShutdownMix();
	UninitializeSDLAudio();
}

void SoundManager::UninitializeMix()
{
	// calling Mix_Init with 0 flag returns whether it is initialized or not. For every Mix_Init call, there should be corresponding Mix_Quit. Hence the loop
	while(Mix_Init(0))
	{
		Mix_Quit();
	}
}

void SoundManager::ShutdownMix()
{
	// for each Mix_OpenAudio call, there must be corresponding Mix_CloseAudio call
	int numOpen = Mix_QuerySpec(nullptr, nullptr, nullptr);
	for (int i = 0; i < numOpen; ++i)
		Mix_CloseAudio();
}

void SoundManager::UninitializeSDLAudio()
{
	if (SDL_WasInit(SDL_INIT_AUDIO) == SDL_TRUE)
	{
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
	}
}




void SoundManager::Release()
{
	delete mInstance;
	mInstance = nullptr;
}

SoundManager &SoundManager::Instance()
{
	if (mInstance == nullptr)
	{
		mInstance = new SoundManager(44100, 1024); // todo: move the values to settings file instead of hardcoding
	}

	return *mInstance;
}


void SoundManager::Play()
{
	mMusic->Play();
}
void SoundManager::Pause()
{
	mMusic->Pause();
}

void SoundManager::Resume()
{
	mMusic->Resume();
}
void SoundManager::Stop()
{
	mMusic->Stop();
}

void SoundManager::Next()
{
	mMusic->Next();
}
void SoundManager::Previous()
{
	mMusic->Previous();
}

void SoundManager::Update(double ticks_passed)
{
	if (mMusic->IsPlaying() && mMusic->MusicFinished())
	{
		mMusic->Next();
	}
}

void SoundManager::PlaySoundEffect(int id)
{
	mSoundEffects->Play(id);
}