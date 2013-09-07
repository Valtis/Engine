#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <SDL.h>
#include "Graphics/Sprite.h"
#include "Utility/UniqueID.h"
class SpriteManager
{
public:
	~SpriteManager();
	static SpriteManager &Instance();
	static void Release();

	void Initialize(std::string datafilePath);

	void AddSprite(std::unique_ptr<Sprite> sprite);
	Sprite *GetSprite(UniqueID id);

	SDL_Texture *GetTextureForDrawing(int spriteSheetID);

private:
	SpriteManager();
	static SpriteManager *mInstance;

	std::unordered_map<UniqueID, std::unique_ptr<Sprite>, UniqueIDHashFunction> mSprites;
	std::unordered_map<int, SDL_Texture *> mSpriteSheets;
};