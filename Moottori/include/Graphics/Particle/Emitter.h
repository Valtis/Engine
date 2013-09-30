#include <vector>
#include "Graphics/Particle/Particle.h"

class Emitter 
{
public:
	Emitter(int particles, SDL_Rect location, double particleLifeTime);

	void Update(double ticks_passed);
	bool IsAlive() { return !mParticles.empty(); }

private:
	void CreateParticles(int particleCount);
	void RemoveDeadParticles();
	void UpdateParticles( double ticks_passed );

	std::vector<Particle> mParticles;
	SDL_Rect mLocation;
};