#include "Graphics/Particle/Particle.h"
#include "Graphics/Particle/ParticleCache.h"
Particle::Particle(double x, double y, double xVelocity, double yVelocity, double lifetimeInTicks) : mX(x), mY(y), 
	mXVelocity(xVelocity), mYVelocity(yVelocity), mLifeTime(lifetimeInTicks), mLifeRemaining(lifetimeInTicks)
{

}

Particle::~Particle()
{

}

void Particle::Initialize(int id)
{	
	mTexture = ParticleCache::Instance().GetRandomTexture(id);
}

void Particle::Update(double ticks_passed)
{
	UpdateLife(ticks_passed);
	UpdateLocation();
}

void Particle::UpdateLife( double ticks_passed )
{
	mLifeRemaining -= ticks_passed;
	if (mLifeRemaining < 0)
	{
		mLifeRemaining = 0;
	}
}


void Particle::UpdateLocation()
{
	mX += mXVelocity;
	mY += mYVelocity;
}

