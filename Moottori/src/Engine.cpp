#include "Engine.h"
#include "Graphics/Renderer/Renderer.h"
Engine::Engine() : mFrameTickLength(0), mLastTick(0)
{

}

Engine::~Engine()
{

}

void Engine::Run() 
{
	Initialize();
	while (true)
	{
		Uint32 currentTick = SDL_GetTicks();
		if (currentTick > mFrameTickLength + mLastTick)
		{
			Renderer::Instance().Draw();
			mLastTick = SDL_GetTicks();
			
		}
	}
	CleanUp();
}


void Engine::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	mLastTick = SDL_GetTicks();
	Renderer::Instance().CreateWindow("Foobar", 640, 480); // move to UI class

	// todo: read from datafile or something
	mFrameTickLength = 100;
}

void Engine::CleanUp()
{
	SDL_Quit();
}