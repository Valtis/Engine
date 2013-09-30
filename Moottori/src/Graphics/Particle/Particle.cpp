#include "Graphics/Particle/Particle.h"
#include "Graphics/SurfaceOperations.h"
#include "Graphics/Renderer/Renderer.h"

Particle::Particle(double x, double y, double xVelocity, double yVelocity, double lifetimeInTicks) : mX(x), mY(y), 
	mXVelocity(xVelocity), mYVelocity(yVelocity), mLifeTime(lifetimeInTicks), mLifeRemaining(lifetimeInTicks)
{

}

Particle::~Particle()
{
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
	}
}

void Particle::Initialize(SDL_Color color)
{	
	SDL_Surface *surface = CreateSurface(color);

	mTexture = SDL_CreateTextureFromSurface(Renderer::Instance().GetRenderingContext(), surface);
	SDL_FreeSurface(surface);

	if (mTexture == nullptr)
	{
		throw std::runtime_error("Failed to allocate texture for particle emitter");
	}
}
SDL_Surface * Particle::CreateSurface( SDL_Color color )
{
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface *surface = SDL_CreateRGBSurface(0, 1, 1, 32, rmask, gmask, bmask, amask);
	if (surface == nullptr)
	{
		throw std::runtime_error("Failed to allocate surface for particle emitter");
	}

	SetSurfaceColor(color, surface);

	return surface;
}


void Particle::SetSurfaceColor( SDL_Color &color, SDL_Surface * surface )
{
	SetRed(0, 0, color.r, surface);
	SetGreen(0, 0, color.g, surface);
	SetBlue(0, 0, color.b, surface);
	SetAlpha(0, 0, color.a, surface);
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

