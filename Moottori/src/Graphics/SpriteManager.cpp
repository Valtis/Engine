#include "Graphics/SpriteManager.h"
#include "Graphics/Renderer/Renderer.h"
SpriteManager *SpriteManager::mInstance = nullptr;

SpriteManager::SpriteManager() 
{

}

SpriteManager::~SpriteManager()
{
	for (auto i : mSpriteSheets)
	{
		SDL_DestroyTexture(i.second);
	}

	mSpriteSheets.clear();
}

SpriteManager &SpriteManager::Instance()
{
	if (mInstance == nullptr)
	{
		mInstance = new SpriteManager();
	}

	return *mInstance;
}

void SpriteManager::Release()
{
	delete mInstance;
	mInstance = nullptr;
}

void SpriteManager::Initialize(std::string datafilePath)
{
	// TODO: Add proper load code here. Hard coded for testing for now
	SDL_Surface *spriteSheetSurface = SDL_LoadBMP("testimap.bmp");

	if (spriteSheetSurface == nullptr)
	{
		throw std::runtime_error("Failed to create surface");
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer::Instance().GetRenderingContext(), spriteSheetSurface);
	
	if (texture == nullptr)
	{
		throw std::runtime_error("Failed to create texture");
	}

	mSpriteSheets[0] = texture;

	SDL_FreeSurface(spriteSheetSurface);
	
}

void SpriteManager::AddSprite(std::unique_ptr<Sprite> sprite)
{
	SDL_assert(sprite != nullptr);
	mSprites[sprite->GetID()] = std::move(sprite);
}

Sprite *SpriteManager::GetSprite(UniqueID id)
{
	if (mSprites.count(id) == 0)
	{
		return nullptr;
	}

	return mSprites[id].get();
}

SDL_Texture *SpriteManager::GetTextureForDrawing(int spriteSheetID)
{
	if (mSpriteSheets.count(spriteSheetID) == 0)
	{
		return nullptr;
	}

	return mSpriteSheets[spriteSheetID];
}