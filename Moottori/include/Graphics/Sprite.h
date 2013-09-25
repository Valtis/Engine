#pragma once
#include <SDL.h>
#include "Utility/UniqueID.h"
class Sprite
{
public:
	Sprite();
	Sprite(int id);
	~Sprite();
	
	SDL_Rect GetLocation() { return mLocation; }
	void SetLocation(SDL_Rect location) { mLocation = location; }
	void SetLocation(int x, int y, int width, int height);

	int GetDrawPriority() 
	{ 
		SDL_assert(mDrawPriority >= 0 && mDrawPriority <=9 ) ;
		return mDrawPriority; 
	}
	void SetDrawPriority(int priority);

	int GetSpriteSheetID() { return mSpriteSheetID; }
	void SetSpriteSheetID(int id) { mSpriteSheetID = id; }

	int GetID() { return mID.AsInt(); }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	Sprite(const Sprite &) = delete;
	Sprite &operator=(const Sprite &) = delete;
#else
private:
	Sprite(const Sprite &);
	Sprite &operator=(const Sprite &);
public:
#endif

private:
	UniqueID mID;
	SDL_Rect mLocation; // location in sprite sheet
	int mSpriteSheetID;
	int mDrawPriority; // value between 0 and 9. Higher value means higher priority, that is, it will be drawn on top of sprites with lower priority

};