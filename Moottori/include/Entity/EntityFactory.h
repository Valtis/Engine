#pragma once

#include <memory>
#include <vector>
#include "Utility/LuaState.h"

class Entity;
class UI;

class EntityFactory
{
public:

	static void RegisterCreationScript(std::string scriptName)
	{
		if (!mLuaStateIsInitialized)
		{
			InitializeLuaState();
		}

		mLuaState.LoadScriptFile(scriptName);

		if (mLuaState.FunctionExists("Initialize"))
		{
			mLuaState.CallFunction("Initialize");
		}
		
	}


	static std::unique_ptr<Entity> CreateEntity(std::string functionName, UI *ui); // todo: hide UI behind interface; needed here so that input component can register itself for input
	static std::unique_ptr<Entity> CreateEntity(std::string functionName) { return CreateEntity(functionName, nullptr); }

private:




	static void AddInputComponent(std::string scriptFile);
	static void AddLocationComponent(int x, int y, std::string scriptFile);
	static void AddGraphicsComponent(std::string scriptFile);
	static void AddSprite(int animationID, int spriteID, int ticksToNextFrame);
	static void AddVelocityComponent(std::string scriptFile);
	static void AddAccelerationComponent(std::string scriptFile);
	static void AddCollisionComponent(int collisionRadius, std::string scriptFile);
	static void AddFactionComponent(int faction, std::string scriptFile);
	static void AddHealthComponent(std::string scriptFile);
	static void AddSoundComponent(std::string scriptFile);

	static void InitializeLuaState();
	static void RegisterMethods();


	static LuaState mLuaState;
	static bool mLuaStateIsInitialized;
	static std::unique_ptr<Entity> mEntityBeingCreated; 
	static UI *mUI; // place holder, figure better way to pass parameters around
};