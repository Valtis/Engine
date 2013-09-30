#include "Graphics/Particle/Emitter.h"
#include "Graphics/Renderer/Renderer.h"
#include "Utility/Random.h"

#include <SDL.h>
#include <algorithm>
#include <fstream>


void Lock_Surface(SDL_Surface *surface)
{
	if (SDL_MUSTLOCK(surface))
	{
		if (SDL_LockSurface(surface) != 0)
		{
			throw std::runtime_error("Failed to lock surface for manipulation");
		}
	}
}

void Unlock_Surface(SDL_Surface *surface)
{
	if (SDL_MUSTLOCK(surface))
	{
		SDL_UnlockSurface(surface);
	}
}

Uint8 GetColor(int x, int y, int width, Uint32 *pixels, Uint32 mask, Uint8 shift, Uint8 loss)
{
	Uint32 temp;
	temp = pixels[y*width + x] & mask;
	temp = temp >> shift;
	temp = temp << loss;
	return (Uint8)temp;
}


void SetColor(int x, int y, int width, Uint32 color, Uint32 *pixels, Uint32 mask, Uint8 shift, Uint8 loss)
{
	pixels[y*width + x] = pixels[y*width + x] ^ (pixels[y*width + x] & mask);
	color = color >> loss;
	color = color << shift;
	pixels[y*width + x] = pixels[y*width + x] | (color);
}

Uint8 GetAlpha(int x, int y, SDL_Surface *surface)
{
	Lock_Surface(surface);
	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	Uint8 retVal = GetColor(x, y, surface->w, pixels, fmt->Amask, fmt->Ashift, fmt->Aloss);
	
	Unlock_Surface(surface);

	return retVal;
}

Uint8 GetRed(int x, int y, SDL_Surface *surface)
{
	Lock_Surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	Uint8 retVal = GetColor(x, y, surface->w, pixels, fmt->Rmask, fmt->Rshift, fmt->Rloss);

	Unlock_Surface(surface);
	return retVal;
}


Uint8 GetGreen(int x, int y, SDL_Surface *surface)
{
	Lock_Surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	Uint8 retVal = GetColor(x, y, surface->w, pixels, fmt->Gmask, fmt->Gshift, fmt->Gloss);

	Unlock_Surface(surface);
	return retVal;
}



Uint8 GetBlue(int x, int y, SDL_Surface *surface)
{
	Lock_Surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	Uint8 retVal = GetColor(x, y, surface->w, pixels, fmt->Bmask, fmt->Bshift, fmt->Bloss);
	
	Unlock_Surface(surface);
	return retVal;
}



void SetAlpha(int x, int y, Uint32 color, SDL_Surface *surface)
{
	Lock_Surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	SetColor(x, y, surface->w, color, pixels, fmt->Amask, fmt->Ashift, fmt->Aloss);
	Unlock_Surface(surface);
}


void SetRed(int x, int y, Uint32 color, SDL_Surface *surface)
{
	Lock_Surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	SetColor(x, y, surface->w, color, pixels, fmt->Rmask, fmt->Rshift, fmt->Rloss);
	Unlock_Surface(surface);
}

void SetGreen(int x, int y, Uint32 color, SDL_Surface *surface)
{
	Lock_Surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	SetColor(x, y, surface->w, color, pixels, fmt->Gmask, fmt->Gshift, fmt->Gloss);
	Unlock_Surface(surface);
}

void SetBlue(int x, int y, Uint32 color, SDL_Surface *surface)
{
	Lock_Surface(surface);
	
	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	SetColor(x, y, surface->w, color, pixels, fmt->Bmask, fmt->Bshift, fmt->Bloss);
	Unlock_Surface(surface);
}



Emitter::Emitter(int particles, SDL_Rect location, double particleLifeTime, double maxSpeed) : mLocation(location)
{
	CreateParticles(particles, particleLifeTime, maxSpeed);
	AllocateBuffer();
}


void Emitter::CreateParticles( int particleCount, double particleLifeTime, double maxSpeed )
{
	for (int i = 0; i < particleCount; ++i) 
	{
		CreateParticle(particleLifeTime, maxSpeed);
	}
}

void Emitter::CreateParticle( double particleLifeTime, double maxSpeed )
{
	std::ofstream debug("debug.txt", std::ios::app);
	double x = mLocation.w/2;
	double y = mLocation.h/2;

	double velocity = Random::GetRandom<double>(maxSpeed, 0.01);
	double angle  = Random::GetRandom<double>(2*3.1415926535);

	Particle particle(x, y, velocity*cos(angle), velocity*sin(angle), particleLifeTime);	
	SetColor(particle);
	debug << "Lifetime: " << particleLifeTime << "\n";
	mParticles.push_back(particle);
}


void Emitter::AllocateBuffer()
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

	mSurface = SDL_CreateRGBSurface(0, mLocation.w, mLocation.h, 32, rmask, gmask, bmask, amask);
	SDL_SetColorKey(mSurface, true, SDL_MapRGB(mSurface->format, 255, 255, 255));

}


Emitter::~Emitter()
{
	SDL_FreeSurface(mSurface);
	SDL_DestroyTexture(mTexture);
}


void Emitter::SetColor( Particle &particle )
{
	SDL_Color color;
	// hard coded for now: either reddish or yellowish particles
	color.r = Random::GetRandom<int>(255, 240);
	color.g = Random::GetRandom<int>(150);
	color.b = 0;
	color.a = 255;
	particle.SetColor(color);
}


void Emitter::Update(double ticks_passed)
{
	UpdateParticles(ticks_passed);
	RemoveDeadParticles();
	UpdateTexture();
}

void Emitter::RemoveDeadParticles()
{
	mParticles.erase(
		std::remove_if(
		mParticles.begin(), mParticles.end(), [](Particle &particle) { return particle.IsDead(); }
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
	ClearBuffer();

	for (auto &particle : mParticles)
	{
		UpdatePixelValueToParticleValues(particle);
	}

	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
	}

	mTexture = SDL_CreateTextureFromSurface(Renderer::Instance().GetRenderingContext(), mSurface);
}

void Emitter::ClearBuffer()
{
	for (int x = 0; x < mLocation.w; ++x)
	{
		for (int y = 0; y < mLocation.h; ++y)
		{
			SetRed(x, y, 0, mSurface);
			SetGreen(x, y, 0, mSurface);
			SetBlue(x, y, 0, mSurface);
			SetAlpha(x, y, 0, mSurface);
		}
	}
}

void Emitter::UpdatePixelValueToParticleValues( Particle &particle )
{
	SDL_assert(!particle.IsDead());
	int x = particle.GetX();
	int y = particle.GetY();
	if (x < 0 || y < 0 ||x >= mLocation.w || y >= mLocation.h )
	{
		return; 
	}

	
	Uint32 value = 0;
	SDL_Color color = particle.GetColor();
	SetRed(x, y, color.r, mSurface);
	SetGreen(x, y, color.g, mSurface);
	SetBlue(x, y, color.b, mSurface);
	SetAlpha(x, y, color.a, mSurface);
}
