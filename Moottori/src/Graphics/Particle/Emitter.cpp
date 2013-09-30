#include "Graphics/Particle/Emitter.h"
#include "Graphics/Renderer/Renderer.h"
#include "Utility/Random.h"

#include <SDL.h>
#include <algorithm>


Emitter::Emitter(int particles, SDL_Rect location, double particleLifeTime) : mLocation(location), mBuffer(nullptr)
{
	CreateParticles(particles, particleLifeTime);
	CreateTexture();
	AllocateBuffer();
}


void Emitter::CreateParticles( int particleCount, double particleLifeTime )
{
	for (int i = 0; i < particleCount; ++i) 
	{
		CreateParticle(particleLifeTime);
	}
}

void Emitter::CreateParticle( double particleLifeTime )
{
	double x = Random::GetRandom<double>(mLocation.w);
	double y = Random::GetRandom<double>(mLocation.h);

	double velocity = Random::GetRandom<double>(10, 5);
	double angle  = Random::GetRandom<double>(2*3.1415926535);

	Particle particle(x, y, velocity*cos(angle), velocity*sin(angle), particleLifeTime);	
	SetColor(particle);
	mParticles.push_back(particle);
}


void Emitter::CreateTexture()
{
	mTexture = SDL_CreateTexture(Renderer::Instance().GetRenderingContext(),
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		mLocation.w, mLocation.h);
}


void Emitter::AllocateBuffer()
{
	mBuffer = new Uint32[mLocation.w*mLocation.h];
}


Emitter::~Emitter()
{
	delete [] mBuffer;
}


void Emitter::SetColor( Particle &particle )
{
	SDL_Color color;
	// hard coded for now: either reddish or yellowish particles
	color.r = Random::GetRandom<int>(255, 240);
	color.g = Random::GetRandom<int>(150);
	color.b = 0;
	color.a = 0;
	particle.SetColor(color);
}


void Emitter::Update(double ticks_passed)
{
	RemoveDeadParticles();
	UpdateParticles(ticks_passed);
	UpdateTexture();
}

void Emitter::RemoveDeadParticles()
{
	mParticles.erase(
		std::remove_if(
		mParticles.begin(), mParticles.end(), [](Particle &particle) { return !particle.IsAlive(); }
	), mParticles.end());
}

void Emitter::UpdateParticles( double ticks_passed )
{
	for (auto &particle : mParticles)
	{
		particle.Update(ticks_passed);
	}
}

void Emitter::UpdateTexture()
{
	for (auto &particle : mParticles)
	{
		UpdatePixelValueToParticleValues(particle);
	}

	SDL_UpdateTexture(mTexture, nullptr, mBuffer, sizeof(Uint32)*mLocation.w);
}

void Emitter::UpdatePixelValueToParticleValues( Particle &particle )
{
	SDL_assert(particle.IsAlive());
	int position = particle.GetX() + particle.GetY() * mLocation.w;

	if (position < 0 || position >= mLocation.h*mLocation.w)
	{
		return; 
	}

	Uint32 value = 0;
	SDL_Color color = particle.GetColor();
	value = value ^ (color.a << 24);
	value = value ^ (color.r << 16);
	value = value ^ (color.g << 8);
	value = value ^ color.b;
	mBuffer[position] = value;
}
