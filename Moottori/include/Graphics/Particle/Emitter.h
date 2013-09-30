#include <vector>

#include "Graphics/Particle/Particle.h"

class Emitter 
{
public:
	Emitter(int particles, SDL_Rect location, double particleLifeTime, double maxSpeed);
	~Emitter();

	void Update(double ticks_passed);


	bool IsAlive() { return !mParticles.empty(); }

	SDL_Texture *GetTexture() { return mTexture; }

	int GetX() { return mLocation.x - mLocation.w/2; }
	int GetY() { return mLocation.y - mLocation.h/2; }
	int GetWidth() { return mLocation.w; }
	int GetHeight() { return mLocation.h; }


private:

	void CreateParticles(int particleCount, double particleLifeTime, double maxSpeed);
	void AllocateBuffer();

	void UpdateTexture();

	void ClearBuffer();

	void UpdatePixelValueToParticleValues(Particle &particle);

	void CreateParticle( double particleLifeTime, double maxSpeed);

	void SetColor( Particle &particle );

	void RemoveDeadParticles();
	void UpdateParticles( double ticks_passed );

	std::vector<Particle> mParticles;
	SDL_Rect mLocation;
	SDL_Texture *mTexture;
	SDL_Surface *mSurface;
};