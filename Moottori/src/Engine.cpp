#include "Engine.h"
#include "Graphics/Renderer/Renderer.h"
#include "Entity/EntityManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/SpriteManager.h"
#include "Event/UIEvent.h"
#include "Utility/Defines.h"
#include "Level/Level.h"

// feel free to delete following headers once refactored, only for testing
#include "Entity/Entity.h"
#include "Entity/EntityFactory.h"
#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"
#include "Graphics/Sprite.h"
#include "Graphics/Camera/EntityTrackingCamera.h"

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
		double ticksPassed = (double)(currentTick - mLastGameLogicTick)/(double)mGameLogicTickLength;
		mLevel->Update(ticksPassed); // todo: replace with level manager code
		mCollisionManager.Update(ticksPassed);
		mLastGameLogicTick = SDL_GetTicks();
	}
	//
}

void Engine::Draw()
{
	Uint32 currentTick = SDL_GetTicks();
	if (currentTick > mDrawTickLength + mLastDrawTick)
	{
		mUI.Draw(); // TODO: pass the ids of current level entities instead of drawing *all* entities, no matter where they are
		mLastDrawTick = SDL_GetTicks();

	}
}


void Engine::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);


	// todo: read from datafile or something
	mDrawTickLength = 30;
	mGameLogicTickLength = 30;


	mUI.Initialize("Generic title - move to settings file!", "data/spritesheets/", 640, 480);
	mUI.RegisterInputHandler([&](Event *event) { return this->InputHandler(event); }, INPUT_PRIORITY_HIGH);

	InitializeInputTypes();


	// --------------- TEST CODE ----------------------
	// --------------- UGLY UGLY UGLY -----------------

	mLevel.reset(new Level(1920, 1080));
	
	std::unique_ptr<Entity> e(new Entity);
	std::unique_ptr<LocationComponent> l(new LocationComponent);
	l->SetX(0);
	l->SetY(0);

	mLevel->AddEntity(e->GetID());

	std::unique_ptr<GraphicsComponent> g(new GraphicsComponent);
	g->AddSprite(0, 200000, 0);

	e->AddComponent(ComponentType::Location, std::move(l));
	e->AddComponent(ComponentType::Graphics, std::move(g));

	Renderer::Instance().AddEntity(e->GetID());
	EntityManager::Instance().AddEntity(std::move(e));

	e.reset(new Entity);
	mLevel->AddEntity(e->GetID());
	l.reset(new LocationComponent);
	l->SetX(200);
	l->SetY(200);

	g.reset(new GraphicsComponent);
	g->AddSprite(0, 200001, 0);

	e->AddComponent(ComponentType::Location, std::move(l));
	e->AddComponent(ComponentType::Graphics, std::move(g));

	Renderer::Instance().AddEntity(e->GetID());
	EntityManager::Instance().AddEntity(std::move(e));

	EntityFactory::RegisterCreationScript("data/scripts/entity_creation.lua");
	
	e = EntityFactory::CreateEntity("CreatePlayer", &mUI);


	mLevel->AddEntity(e->GetID());
	Renderer::Instance().AddEntity(e->GetID());

	// create camera for ui
	std::unique_ptr<Camera> c(new EntityTrackingCamera(e->GetID(), mLevel->GetWidth(), mLevel->GetHeight()));
	mUI.AttachCamera(std::move(c));
	EntityManager::Instance().AddEntity(std::move(e));


	// create asteroid thingy
	e = EntityFactory::CreateEntity("CreateDebugAsteroid");
	mLevel->AddEntity(e->GetID());
	Renderer::Instance().AddEntity(e->GetID());
	EntityManager::Instance().AddEntity(std::move(e));


	mCollisionManager.SetCollidabeEntities(mLevel->GetEntities());
	mCollisionManager.SetLevelWidth(mLevel->GetWidth());
	mCollisionManager.SetLevelHeight(mLevel->GetHeight());

	// END OF TEST CODE

	mLastDrawTick = SDL_GetTicks();
	mLastGameLogicTick = SDL_GetTicks();
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