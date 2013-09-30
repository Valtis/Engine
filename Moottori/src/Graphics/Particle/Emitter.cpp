#include "Graphics/Particle/Emitter.h"
#include "Utility/Random.h"
#include <algorithm>


Emitter::Emitter(int particles, SDL_Rect location, double particleLifeTime) : mLocation(location)
{
	CreateParticles(particles, particleLifeTime);
}

void Emitter::CreateParticles( int particleCount, double particleLifeTime )
{
	for (int i = 0; i < particleCount; ++i) 
	{
		double x = Random::GetRandom<double>(mLocation.w);
		double y = Random::GetRandom<double>(mLocation.h);

		double velocity = Random::GetRandom<double>(10, 5);
		double angle  = Random::GetRandom<double>(2*3.1415926535);

		Particle particle(x, y, velocity*cos(angle), velocity*sin(angle), particleLifeTime);	
		mParticles.push_back(particle);	
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
