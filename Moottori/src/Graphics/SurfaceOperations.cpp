#include "Graphics/SurfaceOperations.h"
#include <stdexcept>
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


