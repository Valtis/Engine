#pragma once
#include "Component.h"

class LocationComponent : public Component 
{
public:
	LocationComponent() : mX(0), mY(0), mRotation(0) {} 
	LocationComponent(int x, int y) : mX(x), mY(y), mRotation(0) {}
	virtual ~LocationComponent() {}

#if !defined _MSC_VER || _MSC_VER >= 1800 
	LocationComponent(const LocationComponent &) = delete;
	LocationComponent &operator=(const LocationComponent &) = delete;
#else
private:
	LocationComponent(const LocationComponent &);
	LocationComponent &operator=(const LocationComponent &);
public:
#endif

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