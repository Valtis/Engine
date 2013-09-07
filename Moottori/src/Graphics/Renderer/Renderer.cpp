#include "Graphics/Renderer/Renderer.h"
#include "Entity/EntityManager.h"
#include <stdexcept>
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


}

void Renderer::Draw()
{
    for (auto it = std::begin(mDrawables); it != std::end(mDrawables); ++it)
    {
        Entity *e = EntityManager::Instance().GetEntity(*it);
		
		if (e == nullptr)
		{
			it = mDrawables.erase(it);
			continue;
		}
        // do stuff with it
        // get graphics, location components, get texture from texturemanager, draw the texture to screen
    }
}
