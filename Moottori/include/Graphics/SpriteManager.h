#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include "Graphics/Sprite.h"
#include "Utility/UniqueID.h"
class SpriteManager
{
public:
	~SpriteManager();
	static SpriteManager &Instance();
	void Release();

	void LoadSprites(std::string datafilePath);
	Sprite *GetSprite(UniqueID id);

private:
	SpriteManager();
	static SpriteManager *mInstance;

	std::unordered_map<UniqueID, std::unique_ptr<Sprite>, UniqueIDHashFunction> mSprites;
};