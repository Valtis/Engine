#include "Graphics/Particle/Emitter.h"
#include <algorithm>


Emitter::Emitter(int particles, SDL_Rect location, double particleLifeTime) : mLocation(location)
{
	CreateParticles(particles);
}

void Emitter::CreateParticles( int particleCount )
{
	for (int i = 0; i < particleCount; ++i) 
	{

	}
}

void Emitter::Update(double ticks_passed)
{
	RemoveDeadParticles();
	UpdateParticles(ticks_passed);
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
