#pragma once
#include "Component.h"
class LocationComponent : public Component 
{
public:
	int GetX() const { return mX; }
	void SetX(int x) { mX = x; }
	
	int GetY() const { return mY; }
	void SetY(int y) { mY = y; }


private:
	int mX;
	int mY;
};