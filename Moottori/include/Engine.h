#pragma once
#include <SDL.h>
class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	void Initialize();
	void CleanUp();
	Uint32 mFrameTickLength;
	Uint32 mLastTick;

};