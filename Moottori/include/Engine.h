#pragma once
#include <SDL.h>
#include <queue>
#include <set>
#include "UI/UI.h"
#include "Collision/CollisionManager.h"
#include "Utility/Enumerations.h"
#include "Utility/LuaState.h"

class Event;
class Entity;
class Level;

class Engine
{
public:
	Engine();
	~Engine();
	
#if (_MSC_VER >= 1800)
	Engine(const Engine &) = delete;
	Engine &operator=(const Engine &) = delete;
#else
private:
	Engine(const Engine &);
	Engine &operator=(const Engine &);
public:
#endif
	void Run();
private:
	void Initialize();
	void InitializeLua();
	
	void CleanUp();
	void HandleInput();
	void UpdateGameState();

	void UpdateScriptState( double ticksPassed );

	void Draw();
	bool InputHandler(Event *event);

	Uint32 mDrawTickLength;
	Uint32 mLastDrawTick;

	Uint32 mGameLogicTickLength;
	Uint32 mLastGameLogicTick;


	bool mIsRunning;

	std::queue<int> mEvents;
	std::set<int> mInterestedInInputs;
	UI mUI;


	LuaState mLuaState;



	// todo: refactor\split to multiple classes - here just so that I get something functional for now
	int AddEntity(const char *scriptName);
	void InitializeInputTypes();
};