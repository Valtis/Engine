#include "Graphics/Particle/Particle.h"


Particle::Particle(double x, double y, double xVelocity, double yVelocity, double lifetimeInTicks) : mX(x), mY(y), 
	mXVelocity(xVelocity), mYVelocity(yVelocity), mLifeTime(lifetimeInTicks), mLifeRemaining(lifetimeInTicks)
{
	mColor.a = 0;
	mColor.r = 0;
	mColor.g = 0;
	mColor.b = 0;
}

void Particle::SetColor(int r, int g, int b)
{
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
	mColor.b = 255;

	mOriginalColor = mColor;
}


void Particle::Update(double ticks_passed)
{
	UpdateLife(ticks_passed);
	UpdateColor();
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

void Particle::UpdateColor()
{
	if (mLifeTime == 0)
	{
		return; 
	}
	/*mColor.r = (double)mOriginalColor.r * (mLifeRemaining/mLifeTime); 
	mColor.g = (double)mOriginalColor.g * (mLifeRemaining/mLifeTime);
	mColor.b = (double)mOriginalColor.b * (mLifeRemaining/mLifeTime);
	mColor.a = (double)mOriginalColor.a * (mLifeRemaining/mLifeTime);*/
}

void Particle::UpdateLocation()
{
	mX += mXVelocity;
	mY += mYVelocity;
}
