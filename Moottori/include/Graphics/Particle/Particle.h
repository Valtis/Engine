#include <SDL.h>
class Particle 
{
public:
	Particle(double x, double y, double xVelocity, double yVelocity, double lifeTime);

	void SetColor(int r, int g, int b);
	void SetColor(SDL_Color color) { mColor = color; mOriginalColor = mColor; } 
	SDL_Color GetColor() { return mColor; }

	void Update(double ticks_passed);
	bool IsDead() { return mLifeRemaining <= 0; }

	int GetX() { return mX; }
	int GetY() { return mY; }

private:

	void UpdateLife( double ticks_passed );
	void UpdateColor();
	void UpdateLocation();
	
	double mX;
	double mY;
	double mXVelocity;
	double mYVelocity;

	double mLifeTime;
	double mLifeRemaining;
	SDL_Color mColor;
	SDL_Color mOriginalColor;
};