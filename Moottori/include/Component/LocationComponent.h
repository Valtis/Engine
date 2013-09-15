#pragma once
#include "Component.h"

class LocationComponent : public Component 
{
public:
	LocationComponent() : mX(0), mY(0), mRotation(0) {} 
	LocationComponent(int x, int y) : mX(x), mY(y), mRotation(0) {}
	virtual ~LocationComponent() {}
	int GetX() const { return mX; }
	void SetX(int x) { mX = x; }
	
	int GetY() const { return mY; }
	void SetY(int y) { mY = y; }

	double GetRotation() { return mRotation; }
	void SetRotation(double r) { mRotation = r; }

protected:
	void OnEventHandlerRegistration() override;
private:
	void HandleLocationChangeEvents(Event *event);
	int mX;
	int mY;
	double mRotation;
};