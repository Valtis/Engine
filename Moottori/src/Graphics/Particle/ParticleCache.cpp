#include "Graphics/Particle/ParticleCache.h"
#include "Utility/Random.h"
#include "Graphics/SurfaceOperations.h"
#include "Graphics/Renderer/Renderer.h"

ParticleCache *ParticleCache::mInstance = nullptr;

ParticleCache &ParticleCache::Instance()
{
	if (mInstance == nullptr)
	{
		mInstance = new ParticleCache();
	}

	return *mInstance;
}

void ParticleCache::Release()
{
	delete mInstance;
	mInstance = nullptr;
}

ParticleCache::~ParticleCache()
{
	for (auto &idTexturePairs: mTextureCache)
	{
		for (auto &texture : idTexturePairs.second)
		{
			SDL_DestroyTexture(texture);
		}
	}
}


void ParticleCache::AddParticle(int id, int r, int g, int b)
{
	SDL_Surface *surface = CreateSurface(r, g, b);
	if (surface == nullptr)
	{
		throw std::runtime_error("Failed to allocate surface for particle emitter");
	}

	SDL_Texture *texture= SDL_CreateTextureFromSurface(Renderer::Instance().GetRenderingContext(), surface);
	SDL_FreeSurface(surface);

	if (texture == nullptr)
	{
		throw std::runtime_error("Failed to allocate texture for particle emitter");
	}

	mTextureCache[id].push_back(texture);
}

SDL_Surface * ParticleCache::CreateSurface(int r, int g, int b )
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

	SetSurfaceColor(surface, r, g, b);

	return surface;
}


void ParticleCache::SetSurfaceColor( SDL_Surface * surface, int r, int g, int b )
{
	SetRed(0, 0, r, surface);
	SetGreen(0, 0, g, surface);
	SetBlue(0, 0, b, surface);
	SetAlpha(0, 0, 255, surface);
}


SDL_Texture *ParticleCache::GetRandomTexture(int id)
{
	int pos = Random::GetRandom<int>(mTextureCache[id].size());
	return mTextureCache[id].at(pos);
}