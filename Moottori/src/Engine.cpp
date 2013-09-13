#include "Engine.h"
#include "Graphics/Renderer/Renderer.h"
#include "Entity/EntityManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/SpriteManager.h"
#include "Event/UIEvent.h"
#include "Utility/Defines.h"

// feel free to delete following headers, only for testing
#include "Entity/Entity.h"
#include "Entity/EntityFactory.h"
#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"
#include "Graphics/Sprite.h"

Engine::Engine() : mDrawTickLength(0), mLastDrawTick(0), mGameLogicTickLength(0), mLastGameLogicTick(0), mIsRunning(true)
{

}

Engine::~Engine()
{

}

void Engine::Run() 
{
	Initialize();
	while (mIsRunning)
	{
		HandleInput();
		UpdateGameState();
		Draw();
	}
	CleanUp();
}

void Engine::HandleInput()
{
	mUI.Update();
	while (!mEvents.empty())
	{
		UIEventType event = mEvents.front();
		mEvents.pop();
		switch (event)
		{
		case UIEventType::Quit:
			mIsRunning = false;
			break;

		default:
			break;
		}
	}
}

void Engine::UpdateGameState()
{
	Uint32 currentTick = SDL_GetTicks();
	if (currentTick > mGameLogicTickLength + mLastGameLogicTick)
	{
		double ticksPassed = (double)(mLastGameLogicTick - currentTick)/(double)mGameLogicTickLength;
		EntityManager::Instance().Update(ticksPassed);
		mGameLogicTickLength = SDL_GetTicks();
	}
	//
}

void Engine::Draw()
{
	Uint32 currentTick = SDL_GetTicks();
	if (currentTick > mDrawTickLength + mLastDrawTick)
	{
		mUI.Draw();
		mLastDrawTick = SDL_GetTicks();

	}
}


void Engine::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	mLastDrawTick = SDL_GetTicks();

	// todo: read from datafile or something
	mDrawTickLength = 30;
	mGameLogicTickLength = 100;

	mUI.Initialize("Generic title - move to settings file!", "data/spritesheets/", 640, 480);
	mUI.RegisterInputHandler([&](Event *event) { return this->InputHandler(event); }, INPUT_PRIORITY_HIGH);

	InitializeInputTypes();


	// --------------- TEST CODE ----------------------
	std::unique_ptr<Sprite> sprite(new Sprite);
	sprite->SetSpriteSheetID(0);
	sprite->SetLocation(0, 0, 50, 50);


	std::unique_ptr<Entity> e(new Entity);
	std::unique_ptr<LocationComponent> l(new LocationComponent);
	l->SetX(0);
	l->SetY(0);

	std::unique_ptr<GraphicsComponent> g(new GraphicsComponent);
	g->AddSpriteID(sprite->GetID().AsInt());

	e->AddComponent(ComponentType::Location, std::move(l));
	e->AddComponent(ComponentType::Graphics, std::move(g));

	Renderer::Instance().AddEntity(e->GetID().AsInt());
	EntityManager::Instance().AddEntity(std::move(e));
	SpriteManager::Instance().AddSprite(std::move(sprite));


	sprite.reset(new Sprite);

	sprite->SetSpriteSheetID(0);
	sprite->SetLocation(51, 0, 50, 50);


	


	e.reset(new Entity);
	l.reset(new LocationComponent);
	l->SetX(200);
	l->SetY(200);

	g.reset(new GraphicsComponent);
	g->AddSpriteID(sprite->GetID().AsInt());

	e->AddComponent(ComponentType::Location, std::move(l));
	e->AddComponent(ComponentType::Graphics, std::move(g));

	Renderer::Instance().AddEntity(e->GetID());
	EntityManager::Instance().AddEntity(std::move(e));
	SpriteManager::Instance().AddSprite(std::move(sprite));

	
	sprite.reset(new Sprite);

	sprite->SetSpriteSheetID(0);
	sprite->SetLocation(102, 102, 50, 50);
	std::vector<int> ids;
	ids.push_back(sprite->GetID().AsInt());

	e = EntityFactory::CreatePlayer(250, 250, 10, ids, mUI);
	Renderer::Instance().AddEntity(e->GetID());
	EntityManager::Instance().AddEntity(std::move(e));
	SpriteManager::Instance().AddSprite(std::move(sprite));



}

void Engine::InitializeInputTypes()
{
	mInterestedInInputs.insert(UIEventType::Quit);
}

bool Engine::InputHandler(Event *event)
{
	UIEvent *uiEvent = dynamic_cast<UIEvent *>(event);
	if (uiEvent == nullptr)
	{
		return false;
	}

	if (mInterestedInInputs.count(uiEvent->GetUIEventType()) != 0)
	{
		mEvents.push(uiEvent->GetUIEventType());
		return true;
	}

	return false;
}

void Engine::CleanUp()
{
	EntityManager::Release();
	SpriteManager::Release();
	Renderer::Release();

	SDL_Quit();
}