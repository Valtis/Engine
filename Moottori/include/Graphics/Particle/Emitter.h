#include <vector>

#include "Graphics/Particle/Particle.h"

class Emitter 
{
public:
	Emitter(int particles, SDL_Rect location, double particleLifeTime);




	~Emitter();

	void Update(double ticks_passed);

	void UpdateTexture();

	void UpdatePixelValueToParticleValues(Particle &particle);

	bool IsAlive() { return !mParticles.empty(); }

	SDL_Texture *GetTexture() { return mTexture; }

	int GetX() { return mLocation.x; }
	int GetY() { return mLocation.y; }

private:

	void CreateParticles(int particleCount, double particleLifeTime);
	void CreateTexture();
	void AllocateBuffer();

	void CreateParticle( double particleLifeTime );

	void SetColor( Particle &particle );

	void RemoveDeadParticles();
	void UpdateParticles( double ticks_passed );

	std::vector<Particle> mParticles;
	SDL_Rect mLocation;
	SDL_Texture *mTexture;
	Uint32 *mBuffer;
};