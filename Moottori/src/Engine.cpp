#include "Engine.h"
#include "Graphics/Renderer/Renderer.h"
#include "Entity/EntityManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/SpriteManager.h"
#include "Utility/LoggerManager.h"
#include "Event/UIEvent.h"
#include "Utility/Defines.h"
#include "Level/Level.h"
#include "Entity/Entity.h"

// feel free to delete following headers once refactored, only for testing

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
		EntityManager::Instance().Update(ticksPassed); 
		mCollisionManager.Update(ticksPassed);
		mLastGameLogicTick = SDL_GetTicks();
	
		UpdateScriptState(ticksPassed);
	}
}

void Engine::UpdateScriptState( double ticksPassed )
{
	if (mLuaState.FunctionExists("OnUpdate"))
	{
		mLuaState.CallFunction("OnUpdate", ticksPassed);
	}
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
	LoggerManager::SetLogFolder("logs");
	LoggerManager::Instance().GetLog(SCRIPT_LOG).SetLoggingLevel(LogLevel::All);
	LoggerManager::Instance().GetLog(SCRIPT_LOG).AddTimeStamps(true);

	SDL_Init(SDL_INIT_VIDEO);
	mLevel.reset(new Level(1920, 1080));
	InitializeLua();

	mUI.Initialize("Generic title - move to settings file!", "data/spritesheets/", 640, 480);
	mUI.RegisterInputHandler([&](Event *event) { return this->InputHandler(event); }, INPUT_PRIORITY_HIGH);

	InitializeInputTypes();
	EntityFactory::RegisterCreationScript("data/scripts/entity_creation.lua");
	mLuaState.CallFunction("OnGameInit");

	// --------------- TEST CODE ----------------------
	// --------------- UGLY UGLY UGLY -----------------

	
	
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


	mCollisionManager.SetCollidabeEntities(mLevel->GetEntities());
	mCollisionManager.SetLevelWidth(mLevel->GetWidth());
	mCollisionManager.SetLevelHeight(mLevel->GetHeight());

	// END OF TEST CODE

	mLastDrawTick = SDL_GetTicks();
	mLastGameLogicTick = SDL_GetTicks();
}

int Engine::GetNumberOfActiveEntities()
{
	return mLevel->GetEntities().size();
}

void Engine::InitializeLua()
{
	mLuaState.Open();
	mLuaState.OpenAllLuaLibraries();
	mLuaState.LoadScriptFile("data/scripts/game.lua");

	luabind::module(mLuaState.State()) [
		luabind::class_<Engine>("Engine")
			.def_readwrite("draw_tick_length", &Engine::mDrawTickLength)
			.def_readwrite("game_logic_tick_length", &Engine::mGameLogicTickLength)
			.def("AddEntity", &Engine::AddEntity)
			.def("AttachCamera", &Engine::CreateAndAttachCamera)
			.def("GetNumberOfActiveEntities", &Engine::GetNumberOfActiveEntities)
	];

	luabind::globals(mLuaState.State())["engine"] = this;
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
	LoggerManager::Release();

	SDL_Quit();
}

int Engine::AddEntity( const char *scriptName )
{
	auto e = EntityFactory::CreateEntity(scriptName , &mUI);
	int id = e->GetID();
	EntityManager::Instance().AddEntity(std::move(e));
	mLevel->AddEntity(id);
	Renderer::Instance().AddEntity(id);

	return id;
}



void Engine::CreateAndAttachCamera( int entityID )
{
	Entity *e = EntityManager::Instance().GetEntity(entityID);
	if (e == nullptr)
	{
		LoggerManager::Instance().GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning, 
			"Could not find entity with id " + std::to_string(entityID) + " for a camera to attach to - aborting");
		return;
	}

	if (e->GetComponent(ComponentType::Location) == nullptr)
	{
		LoggerManager::Instance().GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning, 
			"Entity with id " + std::to_string(entityID) + " does not contain location - cannot attach camera - aborting");
		return;
	}

	std::unique_ptr<Camera> c(new EntityTrackingCamera(entityID, mLevel->GetWidth(), mLevel->GetHeight()));
	mUI.AttachCamera(std::move(c));
}

