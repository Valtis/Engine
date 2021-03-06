#pragma once
#include "Utility/LuaState.h"
class UI;
class EngineScriptInterface
{
public:
	EngineScriptInterface() : mUI(nullptr) { }
	~EngineScriptInterface() { }
	
	void RegisterFunctions(LuaState *state);
	void RegisterUI(UI *ui);
private:

	int SpawnEntity(const char *scriptName, int parentID);
	void PlaySoundEffect(int id);

	void AddParticle(int id, int r, int g, int b);
	void AddEmitter(int id, int x, int y, int numberOfParticles, double lifeTime, double maxVelocity);
	
	void AddLevel(int width, int height);

	void CreateEntityTrackingCamera(int entityID);

	int GetLevelEntitiesCount();

	UI *mUI;
};