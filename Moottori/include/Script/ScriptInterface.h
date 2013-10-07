#pragma once
#include <memory>

#include "Utility/Enumerations.h"
#include "Utility/LuaState.h"
#include "Event/EventSender.h"
#include "Script/EngineScriptInterface.h"
class EventHandler;
class UI;
class ScriptInterface
{
public:

	void RegisterEntityEventHandler(EventHandler *entity);
	void RegisterLuaState(LuaState *state);
	void RegisterMethods();
	void RegisterUI(UI *ui);
private:

	EventSender mEntityEvents;
	EngineScriptInterface mEngineScriptInterface;

	LuaState *mLuaState;
};