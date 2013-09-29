#include "Sound/Music.h"
#include <stdexcept>
#include <fstream>
#include <SDL_mixer.h>
#include <string>

Music::Music() : mMusic(), mCurrentSong(0), mIsPlaying(false)
{
    Mix_VolumeMusic(10);
}

Music::~Music()
{
    Uninitialize();
}

void Music::Initialize()
{
	std::ifstream inFile("data/music/music.dat");

	std::string line;
	while (std::getline(inFile, line))
	{
		ParseLine(line);
	}
}

void Music::ParseLine( std::string &line )
{
	if (line.empty())
	{
		return;
	}

	line = "data/music/" + line;
	Mix_Music *music = Mix_LoadMUS(line.c_str());
	if (music == nullptr)
	{
		throw std::runtime_error("Failed to open music file " + line + " - Error: " + Mix_GetError());
	}
	mMusic.push_back(music);
}



void Music::Uninitialize() 
{
	if (mMusic.size() > 0 && Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}

	for (auto music : mMusic)
	{
		Mix_FreeMusic(music);
	}
	mIsPlaying = false;
	mMusic.clear();
}

void Music::Play()
{
	if (mMusic.empty())
	{
		return;
	}

    Mix_PlayMusic(mMusic[mCurrentSong], 0);
	mIsPlaying = true;
}

void Music::Pause()
{
	Mix_PauseMusic();
}

void Music::Resume()
{
	Mix_ResumeMusic();
}

void Music::Stop()
{
	Mix_HaltMusic();
	mIsPlaying = false;
}

void Music::Next()
{
	++mCurrentSong;
	if (mCurrentSong >= mMusic.size())
	{
		mCurrentSong = 0;
	}
	Play();
}

void Music::Previous()
{
	--mCurrentSong;
	if (mCurrentSong < 0)
	{
		mCurrentSong = mMusic.size() - 1;
	}
	Play();
}

bool Music::IsPlaying()
{
	return mIsPlaying;
}

bool Music::MusicFinished()
{
	return Mix_PlayingMusic();
}

