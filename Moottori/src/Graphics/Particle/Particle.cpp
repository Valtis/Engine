#include "Graphics/Particle/Particle.h"


Particle::Particle(double x, double y, double xVelocity, double yVelocity, double lifetimeInTicks) : mX(x), mY(y), mXVelocity(xVelocity), mYVelocity(yVelocity), mLifeTime(lifetimeInTicks), mLifeRemaining(lifetimeInTicks)
{
	mColor.a = 0;
	mColor.r = 0;
	mColor.g = 0;
	mColor.b = 0;
}

void Particle::SetColor(int r, int g, int b)
{
	mColor.r = 0;
	mColor.g = 0;
	mColor.b = 0;
	mColor.b = 0;
}


void Particle::Update(double ticks_passed)
{
	UpdateLife(ticks_passed);
	UpdateAlpha();
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

void Particle::UpdateAlpha()
{
	mColor.a = 255.0 - 255.0*(mLifeRemaining/mLifeTime);
}

void Particle::UpdateLocation()
{
	mX += mXVelocity;
	mY += mYVelocity;
}
