#pragma once
#include <string>
#include <unordered_map>
#include <vector>
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

	Sprite *GetSprite(int id);

	SDL_Texture *GetTextureForDrawing(int spriteSheetID);

#if !defined _MSC_VER || _MSC_VER >= 1800 
	SpriteManager(const SpriteManager &) = delete;
	SpriteManager &operator=(const SpriteManager &) = delete;
#else
private:
	SpriteManager(const SpriteManager &);
	SpriteManager &operator=(const SpriteManager &);
public:
#endif


private:
	struct SpriteHelper
	{
		int x;
		int y;
		int width;
		int height;
		int spriteSheetID;
		int spriteID;
	};

	SpriteManager();
	static SpriteManager *mInstance;
	void LoadSpriteSheets(std::string datafilePath);
	void LoadSprites(std::string datafilePath);

	std::vector<std::pair<int, std::string>> LoadSpriteSheetDetails(std::string path);
	std::pair<int, std::string> ParseSpriteSheetLine(std::string line, std::string path);
	void LoadSpriteSheet(std::pair<int, std::string> sheet);

	std::vector<SpriteHelper> LoadSpriteDetails(std::string datafilePath);
	SpriteHelper ParseSpriteLine(std::string line, std::string path);
	void CreateSprite(SpriteHelper helper);

	std::unordered_map<int, std::unique_ptr<Sprite>> mSprites;
	std::unordered_map<int, SDL_Texture *> mSpriteSheets;
};