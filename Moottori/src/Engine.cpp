#include "Engine.h"
#include "Graphics/Renderer/Renderer.h"
#include "Entity/EntityManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Sound/SoundManager.h"
#include "Utility/LoggerManager.h"
#include "Event/UIEvent.h"
#include "Utility/Defines.h"
#include "Level/LevelManager.h"
#include "Entity/Entity.h"
#include "Entity/EntityFactory.h"

// feel free to delete following headers once refactored, only for testing
#include "Script/ScriptInterface.h"
#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"
#include "Graphics/Sprite.h"
#include "Graphics/SpriteManager.h"
#include "Graphics/Camera/EntityTrackingCamera.h"


Engine::Engine() : mDrawTickLength(0), mLastDrawTick(0), mGameLogicTickLength(0), mLastGameLogicTick(0), mIsRunning(true)
{

}

Engine::~Engine()
{
	CleanUp();
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

}

void Engine::HandleInput()
{
	mUI.Update();
	while (!mEvents.empty())
	{
		int eventType = mEvents.front();
		mEvents.pop();
		switch (eventType)
		{
			case UI_EVENT_QUIT:
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
		LevelManager::Instance().Update(ticksPassed);
		EntityManager::Instance().Update(ticksPassed); 
	
		CollisionManager::Instance().Update(ticksPassed);
		SoundManager::Instance().Update(ticksPassed);
		mLastGameLogicTick = SDL_GetTicks();
		UpdateScriptState(ticksPassed);
		Renderer::Instance().UpdateEmitters(ticksPassed);
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

	SDL_Init(SDL_INIT_VIDEO);
	InitializeLua();

	mUI.Initialize("Generic title - move to settings file!", "data/spritesheets/", 640, 480);
	mUI.RegisterInputHandler([&](Event *event) { return this->InputHandler(event); }, INPUT_PRIORITY_HIGH);

	InitializeInputTypes();
	EntityFactory::RegisterCreationScript("data/scripts/entity_creation.lua");
	mLuaState.CallFunction("OnGameInit");

	CollisionManager::Instance().SetCollidabeEntities(LevelManager::Instance().GetActiveLevel()->GetEntities());
	CollisionManager::Instance().SetLevelWidth(LevelManager::Instance().GetActiveLevel()->GetWidth());
	CollisionManager::Instance().SetLevelHeight(LevelManager::Instance().GetActiveLevel()->GetHeight());


	mLastDrawTick = SDL_GetTicks();
	mLastGameLogicTick = SDL_GetTicks();
	SoundManager::Instance().Play();

}

int Engine::GetNumberOfActiveEntities()
{
	return LevelManager::Instance().GetActiveLevel()->GetEntities().size();
}

void Engine::InitializeLua()
{
	mLuaState.Open();
	mLuaState.OpenAllLuaLibraries();
	mLuaState.LoadScriptFile("data/scripts/game.lua");
	std::unique_ptr<ScriptInterface> interface(new ScriptInterface());
	interface->RegisterUI(&mUI);
	mLuaState.RegisterScriptEngineInterface(std::move(interface));


	luabind::module(mLuaState.State()) [
		luabind::class_<Engine>("Engine")
			.def_readwrite("draw_tick_length", &Engine::mDrawTickLength)
			.def_readwrite("game_logic_tick_length", &Engine::mGameLogicTickLength)
			.def("AttachCamera", &Engine::CreateAndAttachCamera)
			.def("GetNumberOfActiveEntities", &Engine::GetNumberOfActiveEntities)
	];

	luabind::globals(mLuaState.State())["placeholder"] = this;
}

void Engine::InitializeInputTypes()
{
	mInterestedInInputs.insert(UI_EVENT_QUIT);
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
	SoundManager::Release();
	LevelManager::Release();
	CollisionManager::Release();
	LoggerManager::Release();
	SDL_Quit();
}

void Engine::CreateAndAttachCamera( int entityID )
{
	Entity *e = EntityManager::Instance().GetEntity(entityID);
	if (e == nullptr)
	{
		LoggerManager::GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning, 
			"Could not find entity with id " + std::to_string(entityID) + " for a camera to attach to - aborting");
		return;
	}

	if (e->GetComponent(ComponentType::Location) == nullptr)
	{
		LoggerManager::GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning, 
			"Entity with id " + std::to_string(entityID) + " does not contain location - cannot attach camera - aborting");
		return;
	}

	std::unique_ptr<Camera> c(new EntityTrackingCamera(entityID, 
		LevelManager::Instance().GetActiveLevel()->GetWidth(), LevelManager::Instance().GetActiveLevel()->GetHeight()));
	mUI.AttachCamera(std::move(c));
}

