#include <SDL.h>
class Particle 
{
public:
	Particle(double x, double y, double xVelocity, double yVelocity, double lifeTime);

	void SetColor(int r, int g, int b);
	void SetColor(SDL_Color color) { mColor = color; } 
	SDL_Color GetColor() { return mColor; }

	void Update(double ticks_passed);
	bool IsAlive() { return mLifeRemaining != 0; }

	int GetX() { return mX; }
	int GetY() { return mY; }

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