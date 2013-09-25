#include "Graphics/Sprite.h"

Sprite::Sprite() : mID(), mLocation(), mSpriteSheetID(0), mDrawPriority(0)
{

}

Sprite::Sprite(int id) : mID(id)
{

}

Sprite::~Sprite()
{

}

void Sprite::SetLocation(int x, int y, int width, int height)
{
	mLocation.x = x;
	mLocation.y = y;
	mLocation.w = width;
	mLocation.h = height;
}

void Sprite::SetDrawPriority(int priority)
{
	if (priority < 0)
	{
		priority = 0;
	}

	if (priority > 9)
	{
		priority = 9;
	}

	mDrawPriority = priority;
}
