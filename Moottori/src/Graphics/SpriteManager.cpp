#include "Graphics/SpriteManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Utility/StringUtility.h"

#include <fstream>
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
	LoadSpriteSheets(datafilePath);
	LoadSprites(datafilePath);
}

void SpriteManager::LoadSpriteSheets(std::string datafilePath)
{
	std::vector<std::pair<int, std::string>> spriteSheets = LoadSpriteSheetDetails(datafilePath);
	for (const auto &sheet : spriteSheets)
	{
		LoadSpriteSheet(sheet);
	}
}

std::vector<std::pair<int, std::string>> SpriteManager::LoadSpriteSheetDetails(std::string datafilePath) 
{
	std::vector<std::pair<int, std::string>> spriteSheets;
	std::ifstream inFile(datafilePath + "spritesheets.dat");
	std::string line;
	while (std::getline(inFile, line))
	{
		spriteSheets.push_back(ParseSpriteSheetLine(line, datafilePath));
	}
	return spriteSheets;
}

std::pair<int, std::string> SpriteManager::ParseSpriteSheetLine(std::string line, std::string datafilePath)
{
	std::vector<std::string> tokens = Utility::Tokenize(line, " ");
	if (tokens.size() < 2)
	{
		throw std::runtime_error("Malformed sprite sheet data file: Line " + line + " encourtered");
	}
	return std::make_pair(std::stoi(tokens[1]), datafilePath + tokens[0]);
}

void SpriteManager::LoadSpriteSheet(std::pair<int, std::string> sheet)
{
	SDL_Surface *spriteSheetSurface = SDL_LoadBMP(sheet.second.c_str());

	if (spriteSheetSurface == nullptr)
	{
		throw std::runtime_error("Failed to create surface - does the file " + sheet.second + " exist?");
	}

	SDL_SetColorKey(spriteSheetSurface, true, SDL_MapRGB(spriteSheetSurface->format, 255, 255, 255));
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer::Instance().GetRenderingContext(), spriteSheetSurface);
	SDL_FreeSurface(spriteSheetSurface);

	if (texture == nullptr)
	{
		throw std::runtime_error("Failed to create texture");
	}

	if (mSpriteSheets.count(sheet.first) != 0)
	{
		SDL_DestroyTexture(texture);
		throw std::runtime_error("Spritesheet with id " + std::to_string(sheet.first) + " already exist");
	}

	mSpriteSheets[sheet.first] = texture;	
}



void SpriteManager::LoadSprites(std::string datafilePath)
{
	std::vector<SpriteHelper> spriteData = LoadSpriteDetails(datafilePath);
	for (auto &helper : spriteData)
	{
		CreateSprite(helper);
	}
}

std::vector<SpriteManager::SpriteHelper> SpriteManager::LoadSpriteDetails(std::string datafilePath)
{
	std::vector<SpriteHelper> spriteData;

	std::ifstream inFile(datafilePath + "sprites.dat");
	std::string line;
	while (std::getline(inFile, line))
	{
		spriteData.push_back(ParseSpriteLine(line, datafilePath));
	}
	return spriteData;
}

SpriteManager::SpriteHelper SpriteManager::ParseSpriteLine(std::string line, std::string datafilePath) 
{
	std::vector<std::string> tokens = Utility::Tokenize(line, " ");
	if (tokens.size() < 6)
	{
		throw std::runtime_error("Malformed sprite data file: Line " + line + " encourtered");
	}
	
	SpriteManager::SpriteHelper helper;
	helper.x = std::stoi(tokens[0]);
	helper.y = std::stoi(tokens[1]);
	helper.width = std::stoi(tokens[2]);
	helper.height = std::stoi(tokens[3]);
	helper.spriteSheetID = std::stoi(tokens[4]);
	helper.spriteID = std::stoi(tokens[5]);

	return helper;
}

void SpriteManager::CreateSprite(SpriteManager::SpriteHelper helper)
{
	std::unique_ptr<Sprite> sprite(new Sprite(helper.spriteID));
	sprite->SetSpriteSheetID(helper.spriteSheetID);
	sprite->SetLocation(helper.x, helper.y, helper.width, helper.height);
	mSprites[sprite->GetID()] = std::move(sprite);
}


Sprite *SpriteManager::GetSprite(int id)
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