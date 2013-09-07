#pragma once
#include <SDL.h>
#include "Utility/UniqueID.h"
class Sprite
{
public:
	Sprite();
	~Sprite();
	
	SDL_Rect GetLocation() { return mLocation; }
	void SetLocation(SDL_Rect location) { mLocation = location; }
	void SetLocation(int x, int y, int width, int height);

	int GetDrawPriority() { return mDrawPriority; }
	void SetDrawPriority(int priority);

	int GetSpriteSheetID() { return mSpriteSheetID; }
	void SetSpriteSheetID(int id) { mSpriteSheetID = id; }

	UniqueID GetID() { return mID; }

private:
	UniqueID mID;
	SDL_Rect mLocation; // location in sprite sheet
	int mSpriteSheetID;
	int mDrawPriority; // value between 0 and 9. Higher value means higher priority, that is, it will be drawn on top of sprites with lower priority

};