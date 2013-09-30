#include <SDL.h>
class Particle 
{
public:
	Particle(double x, double y, double xVelocity, double yVelocity, double lifeTime);

	void SetColor(int r, int g, int b);
	SDL_Color GetColor() { return mColor; }

	void Update(double ticks_passed);
	bool IsAlive() { return mLifeRemaining != 0; }

private:

	void UpdateLife( double ticks_passed );
	void UpdateAlpha();
	void UpdateLocation();
	
	double mX;
	double mY;
	double mXVelocity;
	double mYVelocity;
	double mLifeTime;
	double mLifeRemaining;
	SDL_Color mColor;

};