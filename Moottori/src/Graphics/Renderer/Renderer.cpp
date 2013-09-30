#include "Graphics/Renderer/Renderer.h"
#include "Graphics/SpriteManager.h"
#include "Graphics/Sprite.h"
#include "Graphics/Particle/Emitter.h"

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

void Renderer::Draw(Camera *camera)
{
	SDL_assert(camera != nullptr);
	ClearScreen();
	DrawEntities(camera);
	DrawEmitters(camera);
	
	SDL_RenderPresent(mRenderer);
}


void Renderer::ClearScreen()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
}

void Renderer::DrawEntities(Camera *camera)
{
	std::vector<Entity *> drawList = GetEntitiesForDrawing(camera);
	SortByDrawPriority(drawList);
	for (auto it = std::begin(drawList); it != std::end(drawList); ++it)
	{
		DrawEntity(*it, camera);
	}
}

std::vector<Entity *> Renderer::GetEntitiesForDrawing(Camera *camera)
{
	std::vector<Entity *> drawList;
	for (auto it = std::begin(mDrawables); it != std::end(mDrawables); ++it)
    {
        Entity *e = EntityManager::Instance().GetEntity(*it);
		
		if (e == nullptr)
		{
			it = mDrawables.erase(it);
			if (it == std::end(mDrawables))
			{
				break;
			}

			continue;
		}
			
		if (!CullEntity(e, camera))
		{
			drawList.push_back(e);
		}
    }

	return drawList;
}

bool Renderer::CullEntity(Entity *e, Camera *camera)
{
	SDL_assert(camera != nullptr);

	SDL_assert(e != nullptr);
	auto graphics = dynamic_cast<GraphicsComponent *>(e->GetComponent(ComponentType::Graphics));
	auto location = dynamic_cast<LocationComponent *>(e->GetComponent(ComponentType::Location));
	SDL_assert(graphics != nullptr);
	SDL_assert(location != nullptr);

	int spriteID = graphics->GetCurrentSpriteID();
	auto sprite = SpriteManager::Instance().GetSprite(spriteID);
	
	// location within the sprite sheet. We are interested ind width and height params only
	int spriteWidth = sprite->GetLocation().w;
	int spriteHeight = sprite->GetLocation().h;

	// outside right edge
	if (location->GetX() > (camera->GetX() + camera->GetScreenWidth()/2))
	{
		return true;
	}
	// outside bottom edge
	if (location->GetY()  > (camera->GetY() + camera->GetScreenHeight()/2))
	{
		return true;
	}

	// outside left edge
	if (location->GetX() + spriteWidth < (camera->GetX() - camera->GetScreenWidth()/2))
	{
		return true;
	}
	// outside top edge
	if (location->GetY() + spriteHeight < (camera->GetY() - camera->GetScreenHeight()/2))
	{
		return true;
	}
	// some portion is inside current draw region - do not cull
	return false;
}

void Renderer::SortByDrawPriority(std::vector<Entity *> &drawList)
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

void Renderer::DrawEntity(Entity *e, Camera *camera)
{
	auto g = dynamic_cast<GraphicsComponent *>(e->GetComponent(ComponentType::Graphics));
	auto l = dynamic_cast<LocationComponent *>(e->GetComponent(ComponentType::Location));

	SDL_assert(g != nullptr);
	SDL_assert(l != nullptr);

	Sprite *sprite = SpriteManager::Instance().GetSprite(g->GetCurrentSpriteID());
	
	if (sprite == nullptr)
	{
		throw std::runtime_error("Couldn't find sprite with id " + g->GetCurrentSpriteID());
	}

	SDL_Rect drawDst = sprite->GetLocation();

	drawDst.x = l->GetX() - GetCameraXOffset(camera);
	drawDst.y = l->GetY() - GetCameraYOffset(camera);



	SDL_Texture *texture = SpriteManager::Instance().GetTextureForDrawing(sprite->GetSpriteSheetID());

	if (texture == nullptr)
	{
		throw std::runtime_error("Couldn't find sprite sheet with id" + sprite->GetSpriteSheetID());
	}
	SDL_Rect spriteLocation = sprite->GetLocation();

	SDL_RenderCopyEx(mRenderer, texture, &spriteLocation, &drawDst, l->GetRotation(), NULL, SDL_FLIP_NONE);
}


int Renderer::GetCameraXOffset( Camera * camera )
{
	return camera->GetX() - camera->GetScreenWidth()/2;
}

int Renderer::GetCameraYOffset( Camera * camera )
{
	return camera->GetY() - camera->GetScreenHeight()/2;
}


void Renderer::AddEntity( int id )
{
	mDrawables.push_back(id);
}

void Renderer::DrawEmitters(Camera *camera)
{
	for (auto &emitter : mParticleEmitters)
	{
		if (emitter->GetX() + emitter->GetWidth() < camera->GetX() ||
			emitter->GetY() + emitter->GetHeight() < camera->GetY() ||
			emitter->GetX() > camera->GetScreenWidth() ||
			emitter->GetY() > camera->GetScreenHeight())
		{
			continue;
		}
		SDL_Rect location;
		location.x = emitter->GetX() - GetCameraXOffset(camera);
		location.y = emitter->GetY() - GetCameraYOffset(camera);
		location.w = emitter->GetWidth();
		location.h = emitter->GetHeight();
		SDL_RenderCopy(mRenderer, emitter->GetTexture(), nullptr, &location);
	}
}


void Renderer::AddEmitter( std::unique_ptr<Emitter> e )
{
	mParticleEmitters.push_back(std::move(e));
}


void Renderer::UpdateEmitters(double ticks_passed)
{
	mParticleEmitters.erase(
		std::remove_if(
		mParticleEmitters.begin(), mParticleEmitters.end(), [](std::unique_ptr<Emitter> &emitter) { return !emitter->IsAlive(); }
	), mParticleEmitters.end());

	for (auto &emitter : mParticleEmitters)
	{
		emitter->Update(ticks_passed);
	}
}
