#include "Graphics/Renderer/Renderer.h"
#include "Entity/EntityManager.h"

Renderer *Renderer::mInstance = nullptr;


Renderer::Renderer()
{

}

Renderer::~Renderer()
{

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
