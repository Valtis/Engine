#pragma once
#include <SDL.h>
#include <queue>
#include <set>
#include "UI/UI.h"
#include "Utility/Enumerations.h"
class Event;
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
	void InitializeInputTypes();
	void CleanUp();
	void HandleInput();
	void UpdateGameState();
	void Draw();
	bool InputHandler(Event *event);



	Uint32 mDrawTickLength;
	Uint32 mLastDrawTick;

	Uint32 mGameLogicTickLength;
	Uint32 mLastGameLogicTick;


	bool mIsRunning;

	std::queue<UIEventType> mEvents;
	std::set<UIEventType> mInterestedInInputs;
	UI mUI;
};