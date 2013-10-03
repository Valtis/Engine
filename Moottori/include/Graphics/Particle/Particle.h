#pragma once
#include <SDL.h>

class Particle 
{
public:
	Particle(double x, double y, double xVelocity, double yVelocity, double lifeTime);
	~Particle();
	
#if !defined _MSC_VER || _MSC_VER >= 1800 
	Particle(const Particle &) = delete;
	Particle &operator=(const Particle &) = delete;
#else
private:
	Particle(const Particle &);
	Particle &operator=(const Particle &);
public:
#endif

	void Initialize(int id);

	SDL_Texture *GetTexture() { return mTexture; }
	void Update(double ticks_passed);
	bool IsDead() { return mLifeRemaining <= 0; }

	int GetX() { return mX; }
	int GetY() { return mY; }

private:

	void UpdateLife( double ticks_passed );
	void UpdateLocation();

	SDL_Surface *CreateSurface();

	void SetSurfaceColor(SDL_Surface * surface );


	double mX;
	double mY;
	double mXVelocity;
	double mYVelocity;

	double mLifeTime;
	double mLifeRemaining;

	SDL_Texture *mTexture;
};