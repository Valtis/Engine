#include "Graphics/Particle/Emitter.h"

#include "Utility/Random.h"

#include <SDL.h>
#include <algorithm>
#include <fstream>


Emitter::Emitter(int emitterID, int particles, SDL_Rect location, double particleLifeTime, double maxSpeed) : mLocation(location)
{
	CreateParticles(emitterID, particles, particleLifeTime, maxSpeed);
}


void Emitter::CreateParticles(int emitterID, int particleCount, double particleLifeTime, double maxSpeed )
{
	for (int i = 0; i < particleCount; ++i) 
	{
		CreateParticle(emitterID, particleLifeTime, maxSpeed);
	}
}

void Emitter::CreateParticle(int emitterID, double particleLifeTime, double maxSpeed )
{
	double x = mLocation.w/2;
	double y = mLocation.h/2;

	double velocity = Random::GetRandom<double>(maxSpeed, 0.01);
	double angle  = Random::GetRandom<double>(2*3.1415926535);

	std::unique_ptr<Particle> particle(new Particle(x, y, velocity*cos(angle), velocity*sin(angle), particleLifeTime));
	

	particle->Initialize(emitterID);

	mParticles.push_back(std::move(particle));
		
}




Emitter::~Emitter()
{
	SDL_FreeSurface(mSurface);
	SDL_DestroyTexture(mTexture);
}

void Emitter::Update(double ticks_passed)
{
	UpdateParticles(ticks_passed);
	RemoveDeadParticles();
}

void Emitter::RemoveDeadParticles()
{
	mParticles.erase(
		std::remove_if(
		mParticles.begin(), mParticles.end(), [](std::unique_ptr<Particle> &particle) { return particle->IsDead(); }
	), mParticles.end());
}

void Emitter::UpdateParticles( double ticks_passed )
{
	for (auto &particle : mParticles)
	{
		particle->Update(ticks_passed);
	}
}


std::vector<Particle *> Emitter::GetParticles()
{
	std::vector<Particle *> particles;
	for (auto &particle : mParticles)
	{
		particles.push_back(particle.get());
	}

	return particles;

}