#pragma once
#include "Component.h"

class CollisionAreaComponent : public Component
{
public:
	CollisionAreaComponent(int radius) : mRadius(radius) {}
	CollisionAreaComponent() : mRadius(0) {}
	~CollisionAreaComponent() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	CollisionAreaComponent(const CollisionAreaComponent &) = delete;
	CollisionAreaComponent &operator=(const CollisionAreaComponent &) = delete;
#else
private:
	CollisionAreaComponent(const CollisionAreaComponent &);
	CollisionAreaComponent &operator=(const CollisionAreaComponent &);
public:
#endif

	int GetCollisionRadius() const { return mRadius; }
	void SetCollisionRadius(int radius) { mRadius = radius; }

private:
	int mRadius;
};