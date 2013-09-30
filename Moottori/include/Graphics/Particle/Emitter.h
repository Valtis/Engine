#pragma once
#include <vector>

#include <memory>
#include "Graphics/Particle/Particle.h"

class Emitter 
{
public:
	Emitter(int particles, SDL_Rect location, double particleLifeTime, double maxSpeed);
	~Emitter();

	void Update(double ticks_passed);


	bool IsAlive() { return !mParticles.empty(); }

	std::vector<Particle *> GetParticles();

	int GetX() { return mLocation.x - mLocation.w/2; }
	int GetY() { return mLocation.y - mLocation.h/2; }
	int GetWidth() { return mLocation.w; }
	int GetHeight() { return mLocation.h; }


private:

	void CreateParticles(int particleCount, double particleLifeTime, double maxSpeed);
	void CreateParticle( double particleLifeTime, double maxSpeed);

	void SetColor( Particle *particle );

	void RemoveDeadParticles();
	void UpdateParticles( double ticks_passed );

	std::vector<std::unique_ptr<Particle>> mParticles;
	SDL_Rect mLocation;
	SDL_Texture *mTexture;
	SDL_Surface *mSurface;
};