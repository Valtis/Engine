#include "Sound/SoundEffects.h"
#include "Utility/StringUtility.h"
#include <fstream>
#include <string>
#include <stdexcept>

SoundEffects::SoundEffects() : mEffects()
{
}

SoundEffects::~SoundEffects()
{
    Uninitialize();
}

void SoundEffects::Initialize()
{

	std::ifstream inFile("data/sound/soundeffects.dat");

	std::string line;
	while (std::getline(inFile, line))
	{
		ParseLine(line);
	}
}

void SoundEffects::ParseLine( std::string &line )
{
	std::vector<std::string > tokens = Utility::Tokenize(line, " ");

	if (tokens.size() < 2)
	{
		return;
	}

	if (mEffects.count(std::stoi(tokens[1]) != 0))
	{
		return;
	}

	LoadEffect("data/sound/" + tokens[0], std::stoi(tokens[1]));
}


void SoundEffects::LoadEffect( std::string name, int id )
{
	Mix_Chunk *effect = Mix_LoadWAV(name.c_str());

	if (effect == nullptr)
	{
		throw std::runtime_error("Failed to load sound effect " + id);
	}
	mEffects[id] = effect;
}



void SoundEffects::Uninitialize()
{
	for (auto effect : mEffects)
	{
		if (effect.second != nullptr)
		{
			Mix_FreeChunk(effect.second);
		}
	}

	mEffects.clear();
}

void SoundEffects::Play(int id)
{
	if (mEffects.count(id) == 0)
	{
		return;
	}
    Mix_PlayChannel(-1, mEffects[id], 0);
}

