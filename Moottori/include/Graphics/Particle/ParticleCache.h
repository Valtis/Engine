#pragma once
#include <unordered_map>
#include <vector>
#include <SDL.h>

class ParticleCache
{
public:
	~ParticleCache();
	static ParticleCache &Instance();
	static void Release();

	void AddParticle(int id, int r, int g, int b);
	SDL_Texture *GetRandomTexture(int id);

private:
	ParticleCache() {  }
	SDL_Surface *CreateSurface(int r, int g, int b);
	void SetSurfaceColor(SDL_Surface *surface, int r, int g, int b);
	static ParticleCache *mInstance;

	std::unordered_map<int, std::vector<SDL_Texture *>> mTextureCache;
};