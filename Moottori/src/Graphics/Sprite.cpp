#include "Graphics/Sprite.h"

Sprite::Sprite()
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
}