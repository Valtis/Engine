#include "Graphics/Renderer/Renderer.h"
#include "Graphics/SpriteManager.h"
#include "Graphics/Sprite.h"

#include "Entity/EntityManager.h"
#include "Entity/Entity.h"

#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"

#include <stdexcept>
#include <string>
#include <algorithm>

Renderer *Renderer::mInstance = nullptr;


Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
}


Renderer &Renderer::Instance()
{
    if (mInstance == nullptr)
    {
        mInstance = new Renderer();
    }

    return *mInstance;
}

void Renderer::Release()
{
	delete mInstance;
	mInstance = nullptr;
}

void Renderer::CreateWindow(std::string title, int width, int height)
{
	if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &mWindow, &mRenderer) != 0)
	{
		throw std::runtime_error("SDL_CreateWindowAndRenderer failed");
	}

	if (mWindow == nullptr || mRenderer == nullptr)
	{
		throw std::runtime_error("Failed to create window and render context");
	}
	
	SDL_SetWindowTitle(mWindow, title.c_str());

}

void Renderer::Draw()
{
	ClearScreen();
	DrawEntities();

	
	SDL_RenderPresent(mRenderer);
}


void Renderer::ClearScreen()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
}

void Renderer::DrawEntities()
{
	std::vector<Entity *> drawList = GetEntitiesForDrawing();
	SortByDrawPriority(drawList);
	for (auto it = std::begin(drawList); it != std::end(drawList); ++it)
	{
		DrawEntity(*it);
	}
}

std::vector<Entity *> Renderer::GetEntitiesForDrawing()
{
	std::vector<Entity *> drawList;
	for (auto it = std::begin(mDrawables); it != std::end(mDrawables); ++it)
    {
        Entity *e = EntityManager::Instance().GetEntity(*it);
		
		if (e == nullptr)
		{
			it = mDrawables.erase(it);
			continue;
		}
			
		if (!CullEntity(e))
		{
			drawList.push_back(e);
		}
    }

	return drawList;
}

bool Renderer::CullEntity(Entity *e)
{
	// todo: add code here that determines if sprite needs to be drawn at all (is inside draw region)
	return false;
}

void Renderer::SortByDrawPriority(std::vector<Entity *> &drawList) // bool cmp(const Type1 &a, const Type2 &b)
{
	std::sort(std::begin(drawList), std::end(drawList), [](Entity *first, Entity *second) 
	{ 
		auto firstGraphics = dynamic_cast<GraphicsComponent *>(first->GetComponent(ComponentType::Graphics));
		auto secondGraphics = dynamic_cast<GraphicsComponent *>(second->GetComponent(ComponentType::Graphics));
		SDL_assert(firstGraphics != nullptr);
		SDL_assert(secondGraphics != nullptr);
		
		auto firstSprite = SpriteManager::Instance().GetSprite(firstGraphics->GetCurrentSpriteID());
		auto secondSprite = SpriteManager::Instance().GetSprite(secondGraphics->GetCurrentSpriteID());

		if (firstSprite == nullptr)
		{
			throw std::runtime_error("Couldn't find sprite with id " + firstGraphics->GetCurrentSpriteID());
		}

		if (secondGraphics == nullptr)
		{
			throw std::runtime_error("Couldn't find sprite with id " + secondGraphics->GetCurrentSpriteID());
		}

		return firstSprite->GetDrawPriority() < secondSprite->GetDrawPriority();
	}
	);
}

void Renderer::DrawEntity(Entity *e)
{
	auto g = dynamic_cast<GraphicsComponent *>(e->GetComponent(ComponentType::Graphics));
	auto l = dynamic_cast<LocationComponent *>(e->GetComponent(ComponentType::Location));

	SDL_assert(g != nullptr);
	SDL_assert(l != nullptr);

	Sprite *s = SpriteManager::Instance().GetSprite(g->GetCurrentSpriteID());
	
	if (s == nullptr)
	{
		throw std::runtime_error("Couldn't find sprite with id " + g->GetCurrentSpriteID());
	}

	// TODO: Take account the camera position!
	SDL_Rect TEST_DEBUG = s->GetLocation();
	TEST_DEBUG.x = l->GetX();
	TEST_DEBUG.y = l->GetY();

	SDL_Texture *texture = SpriteManager::Instance().GetTextureForDrawing(s->GetSpriteSheetID());

	if (texture == nullptr)
	{
		throw std::runtime_error("Couldn't find sprite sheet with id" + s->GetSpriteSheetID());
	}
	SDL_Rect spriteLocation = s->GetLocation();
	SDL_RenderCopy(mRenderer, texture, &spriteLocation, &TEST_DEBUG);


}