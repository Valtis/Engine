#pragma once
#include "Component.h"

class LocationComponent : public Component 
{
public:
	LocationComponent() : mX(0), mY(0), mRotation(0) {} 
	LocationComponent(double x, double y) : mX(x), mY(y), mRotation(0) {}
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

	int GetX() const { return (int)mX; }
	void SetX(double x) { mX = x; }

	int GetY() const { return (int)mY; }
	void SetY(double y) { mY = y; }

	double GetRotation() { return mRotation; }
	void SetRotation(double r) { mRotation = r; }

protected:
	
	void OnAttachingScript() override;
private:
	double mX;
	double mY;
	double mRotation;
};